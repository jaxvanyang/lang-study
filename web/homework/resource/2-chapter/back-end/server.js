const http = require('http');
const fs = require('fs');
const cache = {};

const port = 8080;

function send404(res) {
    res.writeHead(404, {'Content-Type': 'text/plain'});
    res.write('404! Page not found');
    res.end();
}

function sendPage(res, pagePath) {
    console.log();
    res.writeHead(200, {'Contnt-Type': 'text/html'});
    // res.write(pageContent);
    res.end(pageContent);
}

const server = http.createServer((req, res) => {
    console.log('new request recieved');
    // send404(res);
    var pagePath;
    var pageContent = 'ERROR!';
    if (req.url == '/') {
        pagePath = 'main.html';
    } else {
        pagePath = req.url;
    }
    pagePath = './' + pagePath;
    if (cache[pagePath]) {
        sendPage(res, cache[pagePath])
    } else {
        fs.readFile(pagePath, (err, data) => {
            if (err) throw err;
            else {
                cache[pagePath] = data;
                // console.log(data);
                // console.log(cache[pagePath]);
                sendPage(res, cache[pagePath]);
            }
        });
    }
});

server.listen(port, () => {
    console.log('Server is running on localhost:' + port);
});
