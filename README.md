# door

A simple object movement manager that supports buttons as the default method of
interacting. Doors support multiple buttons, so a button on the inside and
outside of a door is possible. Doors can be opened and closed manually by
calling OpenDoor or CloseDoor. The door state change callbacks can be used to
restrict the use of doors by returning 1.

Documentation is in the source code.

## Installation

Simply install to your project:

```bash
sampctl package install ScavengeSurvive/door
```

Include in your code and begin using the library:

```pawn
#include <door>
```

## Testing

To test, simply run the package:

```bash
sampctl package run
```

And connect to `localhost:7777` to test.
