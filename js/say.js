var say = {};
say.div = null, say.useWebSpeech = false;
say.string = function(txt) {
	if (!say.useWebSpeech) {
		if (say.div == null) {
			say.div = document.createElement("div");
			say.div.style = "position: absolute; left: 0px; top: -400px;";
			say.div.setAttribute("aria-live", "assertive");
			document.body.appendChild(say.div);
		}
		say.div.innerText = text;
		setTimeout(function(){
			say.div.innerText = "";
		}, 10);
		return;
	}
	window.speechSynthesis.cancel();
	setTimeout(function(){
		var msg = new SpeechSynthesisUtterance(txt);
		window.speechSynthesis.speak(msg);
	}, 100);
	return;
};