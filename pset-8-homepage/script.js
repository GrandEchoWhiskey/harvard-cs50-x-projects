$(document).ready(function(){
    $('header').height($(window).height());
});

let lastKnownScrollPosition = 0;
let ticking = false;
let clicked = false;

function addBG(add){
    if(add){
        document.getElementById("navbar").classList.add("bg-dark");
    }else{
        document.getElementById("navbar").classList.remove("bg-dark");
    }
}

document.addEventListener('scroll', function(e) {
lastKnownScrollPosition = window.scrollY;

if (!ticking) {
    window.requestAnimationFrame(function(){
        addBG(lastKnownScrollPosition != 0 || clicked);
    ticking = false;
    });

    ticking = true;
}
});

$('#main_nav_bar').on('show.bs.collapse', function(){
    addBG(true);
});

$(function(){
    $('#main_nav_bar').on('hidden.bs.collapse', function(){
        clicked = false;
        addBG(false || lastKnownScrollPosition != 0);
    })
});

$(function(){
    $("#main_nav_bar").on('show.bs.collapse', function(){
        clicked = true;
        addBG(true);
    })
});