let express = require('express');
let app = express();

app.use(function(req, res, next) {
    res.header("Access-Control-Allow-Origin", "*"); 
    res.header("Access-Control-Allow-Methos", "*"); 
    res.header("Cross-Origin-Embedder-Policy", "require-corp"); 
    res.header("Cross-Origin-Opener-Policy", "same-origin"); 
    next();
})

app.use(express.static('.'))

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/index.html')
})

app.listen(8080, ()=>{
    console.log("http://localhost:8080")
})