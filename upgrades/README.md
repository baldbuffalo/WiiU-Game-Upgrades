# Upgrade Packages

Put your game upgrade packages in this directory.

## Folder layout

Each game gets its own folder:

```
upgrades/
└── YOUR_GAME/
    ├── upgrade.json
    └── upgrade-package/
        └── <your update files>
```

The app scans `sd:/wiiu/apps/WiiUGameUpgrades/upgrades/` at runtime and automatically detects game upgrade folders containing `upgrade.json`.

For packages stored outside the app's SD directory, `upgrade.json` can provide a package URL and SHA-256 value.

See the repository README for the package manifest format.
