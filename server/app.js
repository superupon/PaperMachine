const Koa = require('koa')
const app = new Koa()
const debug = require('debug')('koa-weapp-demo')
const response = require('./middlewares/response')
const bodyParser = require('koa-bodyparser')
const config = require('./config')

var net = require('net')
var HOST = '0.0.0.0'
var PORT = 3000
var socket = 0
// 使用响应处理中间件
app.use(response)

// 解析请求体
app.use(bodyParser())

// 引入路由分发
const router = require('./routes')
app.use(router.routes())

// 启动程序，监听端口
console.info("haha")
app.listen(config.port, () => debug(`listening on port ${config.port}`))

net.createServer(function(sock){
  console.log('connected')
  socket = sock
  sock.on('close', function(data){
    console.log('closed')
  })
  sock.on('data', function(data){
    console.log(data.toString())
    //sock.write('ONE')
  })
}).listen(PORT, HOST)

var timer = setInterval(log, 10000)
function log()
{
  console.log('timer');
  if(socket)
    socket.write('ONE');
}
