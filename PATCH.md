
# yash patch notes

# Version 1.07.2

- Added ability to trace back errors
- All functions have been converted to commands
- New commands:
    - `sleep [seconds=1]: sleep for the given amount of seconds`
	- `trace [index=1]: trace back an error. (1 = last error, 2 = second to last, etc...)`
	- `throw <error> <code> <*message>: throw an error and assign it a value`
	- `sh <*input>: Execute system shell commands`
- Refactored Code
- Closer to Cross Platform availability
- Added documentation



First official release (for real this time)!

NOTE: Function 'throw' is currently having issues and is under further development.

