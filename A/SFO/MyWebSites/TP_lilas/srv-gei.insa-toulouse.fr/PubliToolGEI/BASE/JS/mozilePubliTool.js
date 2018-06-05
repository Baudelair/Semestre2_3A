mozile.save.warn = true;
//mozile.gui.factory = mozile.gui.htmlToolbarPubliTool;
mozile.edit.save = null;
mozile.edit.debug = null;
mozile.gui.htmlToolbar.mainMenu = new mozile.edit.CommandGroup("Main Menu");
mozile.gui.htmlToolbar.mainMenu.image = "Mozile-16";
//mozile.gui.htmlToolbar.mainMenu.addCommand(mozile.gui.htmlToolbar.about);
mozile.gui.htmlToolbar.mainMenu.addCommand(mozile.gui.htmlToolbar.help);
mozile.gui.htmlToolbar._commands = new Array(mozile.gui.htmlToolbar.mainMenu);

publitool_onLoad = function() {
    var old = mozile.edit._commands;
    mozile.edit._commands = new Array();
    for(var i=0; i < old.length; i++) {
	if (i==1 || i > 2)
	    mozile.edit._commands.push(old[i]);
    }
    mozile.edit.addDefaultCommand(mozile.edit.insertText);
    mozile.edit.addDefaultCommand(mozile.edit.removeText);
}

    publitool_saveState = function() {
	if (mozile.edit) mozile.save.savedState = mozile.edit.currentState;
    }