/*clementine = {};

clementine.libraryscanner = {};

clementine.libraryscanner.readDirectory = function(entry) {
  console.log("Reading directory " + entry.name);

  var reader = entry.createReader();

  var callback = function(children) {
    if (children.length == 0) {
      return;
    }

    for (var i = 0; i < children.length; ++i) {
      var child = children[i];
      if (child.isDirectory) {
        clementine.libraryscanner.readDirectory(child);
      } else if (child.isFile) {
        console.log("Reading file " + child.name);
      }
    }

    reader.readEntries(callback);
  };

  reader.readEntries(callback);
};

chrome.fileSystem.chooseEntry({"type": "openDirectory"}, function(entry) {
  if (entry) {
    clementine.libraryscanner.readDirectory(entry);
  }
});*/

document.addEventListener("DOMContentLoaded", function() {
  var listener = document.getElementById("clementine_module_container");
  listener.addEventListener('load', moduleLoaded, true);
  listener.addEventListener('message', handleMessage, true);
});

function moduleLoaded() {
  console.log("loaded");

  ClementineModule = document.getElementById('clementine_module');
  chrome.fileSystem.chooseEntry({"type": "openDirectory"}, function(entry) {
    if (entry) {
      console.log(entry);
      ClementineModule.postMessage({
        "method": "Library.AddDirectory",
        "fileSystem": entry.filesystem,
        "path": entry.fullPath,
        "id": chrome.fileSystem.retainEntry(entry)
      });
    }
  });
}

function handleMessage(event) {
  console.log(event.data);
}
