jQuery(document).ready(function() {
 	var $ = jQuery;
    var screenRes = $(window).width();
    var screenHeight = $(window).height();

    $("[href=#]").click(function(event){
        event.preventDefault();
    });

// Body Wrap
    $(".body_wrap").css("min-height", screenHeight);
    $(window).resize(function() {
        screenHeight = $(window).height();
        $(".body_wrap").css("min-height", screenHeight);
    });

// Dropdown Menu
    $(".dropdown li").hover(function(){
        $(this).addClass('hover');
    },function(){
        $(this).removeClass('hover');
    });

// Remove outline in IE
	$("a, input, textarea").attr("hideFocus", "true").css("outline", "none");

// Add gradient to IE
    setTimeout(function () {
        $("body").addClass("gradient");
    }, 0);

// buttons
    $(".btn").hover(function(){
        $(this).stop().animate({"opacity": 0.8});
    },function(){
        $(this).stop().animate({"opacity": 1});
    });
	$('a.btn, span.btn').on('mousedown', function(){
		$(this).addClass('active')
	});
	$('a.btn, span.btn').on('mouseup mouseout', function(){
		$(this).removeClass('active')
	});

// style Select, Radio, Checkbox
    if ($("select").hasClass("select_styled")) {
        cuSel({changedEl: ".select_styled", visRows: 10});
    }
    if ($("div,p").hasClass("input_styled")) {
        $(".input_styled input").customInput();
    }

// First Child, Last Child
    $("li:first-child, .cusel span:first-child").addClass("first");
    $("li:last-child, .cusel span:last-child").addClass("last");

// NavBar Parents Arrow
    $(".dropdown ul").parent("li").addClass("parent");


// Weather
    $('#allison.weather-forecast li a').click(function() {
        var day = $(this).attr('id');
        $('#allison.weather-forecast li a, .itemAllison').removeClass('active');
        $(this).addClass('active');
        $('.itemAllison.'+day).addClass('active');
        console.log(day);
    });
    $('#donna.weather-forecast li a').click(function() {
        var day = $(this).attr('id');
        $('#donna.weather-forecast li a, #donna.weather-item').removeClass('active');
        $(this).addClass('active');
        $('#donna.weather-item.'+day).addClass('active');
    });
    $('#sergio.weather-forecast li a').click(function() {
        var day = $(this).attr('id');
        $('#sergio.weather-forecast li a, #sergio.weather-item').removeClass('active');
        $(this).addClass('active');
        $('#sergio.weather-item.'+day).addClass('active');
    });





});