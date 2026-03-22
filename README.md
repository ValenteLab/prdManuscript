PROJECT TITLE: Integrated acoustic monitoring and playback: A cost-effective solution for soundscape ecology
Companion repository for the Programmable Research Device (PRD) submitted to HardwareX.
This repository provides firmware, audio cue files, and reproducibility materials associated with the PRD described in the manuscript.

SUMMARY
The Programmable Research Device (PRD) is a low‑cost, field‑ready microcontroller platform designed for ecological monitoring, sensor integration, and automated data collection. This repository contains the firmware used in field deployments, audio cue files used for playback experiments, and documentation intended to ensure full reproducibility in accordance with HardwareX open‑hardware standards.

REPOSITORY CONTENTS

FIRMWARE

LocationCue_Summer2025.ino
Primary firmware used for PRD deployments during Summer 2025.
Implements time‑based cue playback, modular configuration, and manuscript‑quality annotation.

batteryTest.ino
Auxiliary firmware used for battery discharge and runtime testing of PRD hardware configurations.

AUDIO CUE FILES
These WAV files are used by the PRD for playback‑based field experiments.
They are included here to ensure full reproducibility of manuscript methods.

BACS_LocationCue_PrimaryComplex.wav
Primary complex cue for BACS playback trials.

NOBO_LocationCue_Song.wav
Song cue used for NOBO playback trials.

PRAW_LocationCue_SongA+B.wav
Combined cue used for PRAW playback trials.

PLAY.wav
Generic playback test file used for device validation and troubleshooting.

DOCUMENTATION

README.md
GitHub‑formatted documentation (this file).

OTHER

.gitignore
Standard ignore rules for Arduino, audio files, and manuscript‑related artifacts.

HARDWARE OVERVIEW
The PRD is built around a microcontroller‑based architecture designed for low‑power field operation, modular sensor integration, flexible timing and cue‑based event triggering, and transparent, reproducible firmware workflows.

Core components (as described in the manuscript) include:

- Microcontroller (e.g., Arduino Nano or Nano Every)
- Real‑time clock module (if applicable)
- Power regulation and battery system
- MicroSD card module for audio file storage
- Audio amplifier and speaker for cue playback
- Optional sensors or peripheral modules depending on deployment

A full Bill of Materials (BOM) will be included in the final manuscript supplement and linked here.

FIRMWARE DETAILS

LocationCue_Summer2025.ino
This firmware controls timed playback of species‑specific audio cues.
Features include:

- Time‑based cue generation
- Modular configuration for different deployment types
- WAV file playback from microSD
- Manuscript‑quality annotation for transparency and reproducibility
- Logging and safety checks (as described in the manuscript)

batteryTest.ino
This firmware is used to characterize battery performance under realistic PRD loads.
Features include:

- Continuous or periodic playback cycles
- Logging of runtime behavior
- Support for multiple battery chemistries and capacities

UPLOAD INSTRUCTIONS

- Open Arduino IDE (version 2.x recommended).
- Load the desired .ino file.
- Select the appropriate board and port.
- Install any required libraries listed at the top of the file.
- Upload the firmware to the device.

AUDIO CUE FILES
All WAV files included in this repository were used in manuscript‑reported field trials.
They are provided to ensure exact reproducibility of playback experiments.

File descriptions:

- BACS_LocationCue_PrimaryComplex.wav: Primary complex cue for BACS trials.
- NOBO_LocationCue_Song.wav: Song cue for NOBO trials.
- PRAW_LocationCue_SongA+B.wav: Combined cue for PRAW trials.
- PLAY.wav: Generic test cue for device validation.

DIRECTORY STRUCTURE
prdManuscript/
- LocationCue_Summer2025.ino
- batteryTest.ino
- BACS_LocationCue_PrimaryComplex.wav
- NOBO_LocationCue_Song.wav
- PRAW_LocationCue_SongA+B.wav
- PLAY.wav
- README.md
- .gitignore

REPRODUCIBILITY
This repository supports HardwareX open‑hardware principles by providing:

- Public access to firmware used in the manuscript
- Audio cue files used in field experiments
- Version‑controlled development history
- Clear documentation of device behavior
- A foundation for replication, modification, and extension

As the manuscript moves through review, additional reproducibility materials will be added, including:

- Wiring diagrams
- PCB or perfboard layout
- Full bill of materials
- Assembly instructions
- Validation datasets (if appropriate)

VALIDATION
Validation procedures, performance metrics, and field‑testing results are described in detail in the manuscript.
This repository will host any supplementary validation scripts or data referenced in the article.

CONTRIBUTING
Contributions are welcome, especially from researchers adapting the PRD for new applications.

To contribute:

- Fork the repository.
- Create a feature branch.
- Commit changes with clear, descriptive messages.
- Open a pull request.

For major changes, please discuss them with the maintainers first.

LICENSE
This repository is released under the Creative Commons Attribution (CC‑BY) license.
Users are free to share and adapt the materials provided here, including firmware and audio files, provided that appropriate credit is given to the original authors.

ACKNOWLEDGMENTS
This repository accompanies the PRD manuscript developed by the Valente Lab at Auburn University.
We thank all collaborators contributing to firmware development, field testing, and manuscript preparation.
