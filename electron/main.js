const {BrowserWindow, app} = require('electron');
			os = require('os'),
			path = require('path'),
			chokidar = require('chokidar');

let win;

var watcher = chokidar.watch(process.argv[2]);
watcher.on('change', path => win.webContents.send('changed', path))

function createWindow() {
	win = new BrowserWindow({width: 800, height: 600, 'title-bar-style': 'hidden'});
  win.loadURL(`file:///${__dirname}/virtual.html`);
  win.webContents.on('did-finish-load', () => {
	  win.webContents.send('new', process.argv[2])
	});
}

app.on('ready', createWindow);

app.on('window-all-closed', () => {
	if (process.platform !== 'darwin') {
		app.quit();
	}
});

app.on('activate', () => {
	if (win === null) {
		createWindow();
	}
});
