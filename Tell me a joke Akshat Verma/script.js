let jokeSection = document.getElementById("joke-box")
let jokeBtn = document.querySelector(".btn")

let API =
"https://v2.jokeapi.dev/joke/Any?blacklistFlags=nsfw,religious,political,racist,sexist,explicit&type=single";

const acquireJoke = ()=>{

jokeSection.classList.remove("content-fade")

fetch(API)
    .then((info)=> info.json())
    .then((item)=>{
        jokeSection.textContent = `${item.joke}`
        jokeSection.classList.add("content-fade")
    })

}

jokeBtn.addEventListener("click", acquireJoke);