# Project Structure

## Goal

This repository was reorganized to make the firmware easier to read, easier to navigate, and easier to maintain without changing the elevator behavior on purpose.

## Structure

```text
firmware/
  include/
    app/
      elevator_control.h
      elevator_state_machine.h
    bsp/
      input_config.h
      output_config.h
    platform/
      eusart1.h
      interrupt_manager.h
      mcc.h
      system_init.h

  src/
    app/
      main.c
      elevator_control.c
      elevator_state_machine.c
    bsp/
      input_config.c
      output_config.c
    platform/
      eusart1.c
      interrupt_manager.c
      mcc.c
      system_init.c
```

## Naming Rules

- Source files use lowercase names with underscores.
- Headers are grouped by role in `include/`.
- Application-specific code is separated from platform-generated code.
- Board support code is separated from platform code.
- Entry point code is separated from the state machine and startup logic.

## Refactor Scope

This refactor includes:
- folder reorganization
- file renaming
- include path cleanup
- several function-name corrections for readability
- header cleanup to reduce unnecessary coupling
- removal of unused modules

This refactor does not intentionally change:
- relay behavior
- movement timing
- interrupt priorities
- serial communication behavior

## Known Gaps

- The MPLAB project files are still not committed.
- `elevator_control.c` remains large and could still be split into smaller driver-oriented modules in a future pass.
