let name = null;

document.querySelector('#connect').addEventListener('click', (e) => {
    e.preventDefault();

    const socket = new WebSocket(' ws://floating-harbor-11933.herokuapp.com', ['echo-protocol']);

    socket.onopen = function (e) {
        name = document.querySelector('#name').value;
        socket.send(JSON.stringify({
            type: 'setup',
            name,
            bet: 'A4'
        }));
    };

    document.querySelector('#doBet').addEventListener('click', (e) => {
        e.preventDefault();

        socket.send(JSON.stringify({
            type: 'bet',
            name,
            bet: document.querySelector('#bet').value
        }))
    })

    socket.onclose = (e) => {
        console.log('Connection closed');
    }

    socket.onmessage = (e) => {
        const data = JSON.parse(e.data);

        if (data.type === 'connected') {
            document.querySelector('#connect').enabled = false;
            document.querySelector('#youName').innerText = data.name;
        }
        else if (data.type === 'bet') {
            console.log('you bet: ' + data.bet);
        }
        else if (data.type === 'info') {
            document.querySelector('#seconds').innerText = data.seconds;
        }
        else if (data.type === 'result') {
            console.log(data.winners);
            document.querySelector('#winners').innerText = `win bet: ${data.winBet}, winners: ${data.winners}`;
        }
    }
});