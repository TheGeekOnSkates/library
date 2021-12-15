/**
 * Parses a string as if it were a set of command-line arguments
 * @param {string} str The string to parse
 * @returns {Array<string>} The command-line arguments
 * @remarks This was created with the idea of improving efficiency
 * in accessibility scripting scenarios; things that take a mouse
 * user 4-5 clicks take even longer for keyboard users, so being able
 * to just type i.e. dial 4078982483 or lookup "Client Name" and have
 * a script do it would be a bit more efficient (it also means users
 * wouldn't have to memorize a bazillion hotkeys - they could pick
 * the action from a dropdown menu and then type the other parameters
 * or whatever; obviously this depends heavily on the situation, but
 * at least it's something we can do if we want to)
 */
function parseArgs(str) {
	var inQuotes = false, arg = '', args = [];
	for (var i=0; i<str.length; i++) {
		if (inQuotes) {
            if (str[i] == '\\' && str[i - 1] != '\\') continue;
            if (str[i] == '"') {
                if (str[i - 1] !== '\\') {
                    inQuotes = false;
                    continue;
                }
            }
			arg += str[i];
		}
		else if (str[i] == '"') {
			inQuotes = true;
		}
		else if (str[i] == ' ') {
			args.push(arg);
			arg = '';
		}
		else arg += str[i];
	}
	if (arg != '') args.push(arg);
	return args;
}

var run = {
    "test-1": {
        main: function(args) {
            print(args.length);
        }
    },
    "test-2": {
        main: function(args) {
            print(args[1]);
        }
    },
};

var actions = [
    parseArgs('test-1 1 2 3 4 5 6'),
    parseArgs('this-should-throw'),
    parseArgs('test-2 "Awesome, it works!"')
];
for (var i=0; i<actions.length; i++) {
    var a = actions[i];
    try {
        run[actions[i][0]].main(actions[i]);
    }
    catch(e) {
        print("Error running program");
    }
}



