// function SendPass(){
// 	let pass = document.getElementById('passtext').value;
// 	let correct = document.getElementById('correct');
// 	var request = new XMLHttpRequest();
//     request.open("POST", '/' + pass);

//     // Функция обратного вызова, когда запрос завершен
//       request.onload = () => {
// 		  correct.innerHTML = request.responseText;
//       }

//     request.send();
// }

const URL = 'http://localhost:5000/calculate';

window.addEventListener('DOMContentLoaded', () => {
    document.querySelector('#send-data').addEventListener('click', async (e) => {
        e.preventDefault();
        const aBorder = document.querySelector('#a-border').value;
        const bBorder = document.querySelector('#b-border').value;

        if (aBorder === '' || bBorder === '') {
            alert('заполните поля!');
            return;
        }

        console.log(aBorder + ":" + bBorder);

        const fetchResult = await fetch(`${URL}calculate?a=${aBorder}&b=${bBorder}`);

        const json = await fetchResult.json();

        //console.log(json);

        document.querySelector('#response').innerText = json.result;
    });
});