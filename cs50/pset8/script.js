$("#submitted").on("click", (e) => {
    e.preventDefault();
    $("form").hide();
    $("#done").html("<p>Done!</p>")
})