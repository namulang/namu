window.addEventListener('resize', function(event) {
  resizeCodePad();
}, true);

function highlight(ta) {
    let highlighted = hljs.highlight(ta.value, { language: "namu"}).value
    document.getElementById("pre_codepad").innerHTML = highlighted;
}
function inputTab(textArea) {
    if (event.key == 'Tab') {
        event.preventDefault();
        var start = textArea.selectionStart;
        var end = textArea.selectionEnd;

        textArea.value = textArea.value.substring(0, start) + "    " + textArea.value.substring(end);

        // put caret at right position again
        textArea.selectionStart = textArea.selectionEnd = start + 4;
      }
}

function runScript(frameId, srcId) {
    var bottom = document.getElementById('result');
    bottom.style.display = 'block';

    runNamuTextArea(frameId, srcId);
    showCloseButton();
    resizeCodePad();
}

function showCloseButton() {
    const close = document.getElementById('bt-close');
    close.style.setProperty('display', 'block');
}

function onclickCloseButton() {
    const close = document.getElementById('bt-close');
    close.style.setProperty('display', 'hidden');

    var bottom = document.getElementById('result');
    bottom.style.display = 'none';
    resizeCodePad();
}

function resizeCodePad() {
    let ta = document.getElementById("ta_codepad");
    let pre = document.getElementById("pre_codepad");
    let preStyle = window.getComputedStyle(document.getElementById('pre_codepad'))
    //ta.style.paddingLeft = (pre.offsetLeft + 50) + "px";
    //ta.style.paddingTop = pre.offsetRight + "px";
    ta.style.width = pre.offsetWidth;
    ta.style.height = preStyle.height;
}

function onchangeSrc(value) {
    var codepad = document.getElementById('ta_codepad');
    switch(value) {
        case 'hello-world': codepad.value = `
# Hello, I'm Namu language.
# Please edit your code freely and press button in the top right to run.
# Refer to the 'guide' section above for more syntax.
main() void
    print("hello world!")`;
            break;


        case 'bow-to-everyone': codepad.value = `
def person
    name := "default"
    bow() str
        print("hello. I'm " + name + "\\n")
        name

main() void
    mike := person()
    mike.name = "mike"

    last := for p in {mike, mike(), mike(mike)}
        p.bow()

    print("and second one was " + last[1])`;
            break;
    }
    highlight(document.getElementById("ta_codepad"))
}

window.onload = function() {
  onchangeSrc('hello-world');
  resizeCodePad();
}

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