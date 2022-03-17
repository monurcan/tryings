const express = require('express')
const bodyParser = require('body-parser')
const app = express()

// ajout de socket.io
const server = require('http').Server(app)
const io = require('socket.io')(server)

app.use(bodyParser.json())
app.use(bodyParser.urlencoded({extended:true}))
app.use(express.static('public'))
app.get('/', function (req, res) {
   res.sendFile('index.html', { root: __dirname })
})

io.on('connection', function (socket) {
  socket.on('message', function (data) {
    //socket.broadcast.emit('message', data); // (1)
    //console.log(data);
    io.sockets.emit('message', data);
  });
});

// on change app par server
server.listen(3000, function () {
 console.log('Running.')
})