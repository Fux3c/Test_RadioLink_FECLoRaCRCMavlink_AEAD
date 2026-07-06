#include "missionmanager.h"
#include "utils/flightlogfactory.h"

MissionManager::MissionManager(FlightModels &avionics_models, FlightModels &payload_models, QObject *parent) : QObject(parent), m_avionics_models(avionics_models), m_payload_models(payload_models), m_state(CaptureState{}) {}

QString MissionManager::missionName() const {return m_missionName;}

QString MissionManager::modeText() const
{
    if (!isPlayback()) return "Capture Mode";
    return "Playback Mode";
}

void MissionManager::setMissionName(const QString &name) {
    if (name != m_missionName) {
        m_missionName = name;
        emit missionNameChanged();
    }
}

bool MissionManager::importMissionData(const QString &path)
{
    const ParsedFlightLog data = FlightLogFactory::parse(path);
    if (!data.valid) return false;

    FlightLogFactory::populateAltitude(m_avionics_models.altitude, data);
    FlightLogFactory::populateVelocity(m_avionics_models.velocity, data);
    if (m_avionics_models.state)
        FlightLogFactory::populateState(m_avionics_models.state, data);
    FlightLogFactory::populateLocation(m_avionics_models.location, data);

    m_state = PlaybackState {
        path
    };
    emit stateChanged();

    return true;
}

bool MissionManager::isPlayback() const {
    return std::holds_alternative<PlaybackState>(m_state);
}

/**
 *	Though Capture mode is default state, we want to be able to start capture mode again after user has dismissed playback mode
 */
void MissionManager::startCapture() {
    m_state = CaptureState {};
    emit stateChanged();
}
