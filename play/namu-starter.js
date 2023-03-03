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
