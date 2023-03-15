function runNamuSrc(iframeId, src) {
    var iframe = document.getElementById(iframeId);
    var win = iframe.contentWindow;
    iframe.onload = function() {
        win.postMessage(src, '*');
    }
    win.location.reload();
}
function runNamuTextArea(iframe, srcId) {
    var src = document.getElementById(srcId);
    runNamuSrc(iframe, src.value);
}
function runNamuDiv(postfix) {
    var src = document.getElementById("ta"+postfix);
    var play = document.getElementById("bt"+postfix);
    runNamuSrc("fr"+postfix, src.textContent);
    play.style.display = 'none';
}