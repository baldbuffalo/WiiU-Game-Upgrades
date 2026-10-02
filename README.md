# WiiU Game Upgrades

A Wii U Aroma homebrew application for installing user-created game upgrade packages.

## Status

The application is being built around an Aroma/WUT C++ application. The repository contains the complete application architecture: catalog loading, package validation, download handling, local staging, and an installer abstraction.

**Important:** installing modified game content as a persistent title-level upgrade is platform-specific. This project deliberately does not pretend that a normal Nintendo `0005000E` update can be created by simply replacing files. The installer backend must use a Wii U/Aroma-supported mechanism appropriate to the package format.

## Build

Requires devkitPro Wii U development packages, WUT and the Wii U application rules.

```sh
make
```

## Repository package format

The catalog is JSON. Each upgrade declares:

- target game Title ID
- upgrade version
- minimum supported base version
- package URL
- SHA-256
- human-readable changelog

The application verifies metadata before staging an upgrade.

## Runtime

1. Load the catalog.
2. Display available upgrades.
3. Select an upgrade.
4. Validate the target Title ID/version.
5. Download the package to SD.
6. Verify SHA-256.
7. Stage the package.
8. Pass the staged package to the platform installer backend.
9. Keep the installed result independent of this application.

No Nintendo server is required by the application after a package has been installed.


## Where to put an update package

Put each update in its own folder under `upgrades/`:

```
upgrades/
└── YOUR_GAME/
    ├── upgrade.json
    └── update.zip
```

The Aroma app automatically scans `sd:/wiiu/apps/WiiUGameUpgrades/upgrades/` when it starts. If both files are present and the manifest is valid, it detects `update.zip` automatically.