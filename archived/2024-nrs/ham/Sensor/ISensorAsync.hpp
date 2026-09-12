#pragma once
#include <functional>
class ISensorAsync
{
public:
    typedef std::function<void()> Callback;
private:
    Callback m_onNewReadingAvailable;
public:
    ISensorAsync(const Callback& onNewReadingAvailable):
                m_onNewReadingAvailable{onNewReadingAvailable}
    { }
    virtual bool initiate() = 0;
    virtual bool startReading() = 0;
    virtual void onReadingComplete() = 0;
    void onNewReadingAvailable(){
        if(m_onNewReadingAvailable)
            m_onNewReadingAvailable();
        };
};

