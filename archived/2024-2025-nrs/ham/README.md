# Horizon Abstraction Middleware 🚀
Horizon Abstraction Middleware (HAM) serves as abstraction layer to streamline and enhance the development of rocket avionics, providing standardized user-friendly components. 

# Doxygen
## Install
```shell
winget install doxygen
winget install graphviz
```
Optional [extension](https://marketplace.visualstudio.com/items?itemName=cschlosser.doxdocgen) for vscode. 

## Usage
```cpp
 /**
 * @brief Sets the logical state of pin.
 * 
 * @param state High or Low
 */
void Set(const bool& state);
/**
 * @brief Gets the digital state of the pin.
 * 
 * @return bool   => Logical high
 * @return false  => Logical low
 */
const bool Get() const;
```
- [Introduction](https://www.doxygen.nl/manual/docblocks.html#cppblock)
- [Reference](https://www.doxygen.nl/manual/commands.html)
