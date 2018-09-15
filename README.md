# Friendly Changelog

## Contributing

A simple `npm install` will get all of the dev dependecies you need to compile and run this project. Additionally, the following npm scripts should come in handy:

- `npm run build` to compile the ReasonML and bundle it
- `npm run clean` to clean up build artifacts if something goes wrong
- `npm run serve` to run the other two scripts, plus start a server on 8080 watching the `dist` folder for changes

[OCaml and Reason IDE by Darin Morrison](https://marketplace.visualstudio.com/items?itemName=freebroccolo.reasonml) is a good plugin for working with the ReasonML in vscode. My build task (in `.vscode/tasks.json`) looks like this:

```
{
  // See https://go.microsoft.com/fwlink/?LinkId=733558
  // for the documentation about the tasks.json format
  "version": "2.0.0",
  "tasks": [
    {
      "type": "npm",
      "script": "build",
      "group": {
        "kind": "build",
        "isDefault": true
      }
    }
  ]
}

```
