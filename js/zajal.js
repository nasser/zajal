const {ipcRenderer} = require("electron"),
      fs = require("fs")

ipcRenderer.on('new', (event, path) => {
  fs.readFile(path, "utf8", (err, source) => {
    console.log(source);
    clojurescript.core.eval(source);
  })
})

ipcRenderer.on('changed', (event, path) => {
  // hack
  var oldTitle = document.title;
  document.title = document.title + "*";
  fs.readFile(path, "utf8", (err, source) => {
    clojurescript.core.eval(source);
    document.title = oldTitle;
  })
})