const http = require('http');
const fs = require('fs');
const mime = require('mime');
const path = require('path');
const cache = {};

const port = 8080;

function send404(res) {
    res.writeHead(404, { 'Content-Type': 'text/plain' });
    res.write('404! Page not found');
    res.end();
}

function sendFile(res, filePath, fileContent) {
    res.writeHead(200, { 'Content-Type': mime.getType(path.basename(filePath)) });
    res.end(fileContent);
}

const server = http.createServer((req, res) => {
    console.log('req.url = ' + req.url);
    var filePath;
    if (req.url == '/') {
        filePath = 'main.html';
    } else {
        filePath = req.url;
    }
    if (filePath[0] == '/') {
        filePath = '.' + filePath;
    } else {
        filePath = './' + filePath;
    }
    if (cache[filePath]) {
        sendFile(res, filePath, cache[filePath])
    } else {
        fs.readFile(filePath, (err, data) => {
            if (err) console.log('file: ' + filePath + ' not found');
            else {
                cache[filePath] = data;
                sendFile(res, filePath, cache[filePath]);
            }
        });
    }
});

server.listen(port, () => {
    console.log('Server is running on localhost:' + port);
});
