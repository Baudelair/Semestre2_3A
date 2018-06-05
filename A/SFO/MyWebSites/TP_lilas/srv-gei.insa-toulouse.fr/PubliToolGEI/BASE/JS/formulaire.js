mode = "pasdisplay";
var frm1;
var frm2;
publitool_onLoad = null;

publitool_saveState = null;

window.onload = function() {
    if (publitool_onLoad) publitool_onLoad();
}

// recharge la frame passée en paramètre
function rechargerFrame (nomFrame) {
    if (parent.frames[nomFrame]) {
	parent.frames[nomFrame].location.reload(true);
	//parent.frames[nomFrame].location.load(parent.frames[nomFrame].location);
    } else {
	alert("pas de frame "+nomFrame);
    } 
}

function chargerUrlDansFrame(nomFrame, url) {
    if (parent.frames[nomFrame]) {
	parent.frames[nomFrame].window.location=url;
    } else alert("Frame non trouvée : "+nomFrame);
}

function ecrireDocHtmlDansFrame(nomFrame, docHtml) {
    if (parent.frames[nomFrame]) {
	parent.frames[nomFrame].document.open("text/html","replace");
	parent.frames[nomFrame].document.write(docHtml);
	parent.frames[nomFrame].document.close();
    } else alert("Frame non trouvée : "+nomFrame);
}

function ecrireDocHtmlFrame1ChargerFrame2(nomFrame1, doc, nomFrame2, url) {
    //chargerUrlDansFrame(nomFrame2, url);
    if (parent.frames[nomFrame2]) {
	parent.frames[nomFrame2].window.location=url;
    } else alert("Frame non trouvée : "+nomFrame2);

    //ecrireDocHtmlDansFrame(nomFrame1, doc);
    if (parent.frames[nomFrame1]) {
	parent.frames[nomFrame1].document.open("text/html","replace");
	parent.frames[nomFrame1].document.write(docHtml);
	parent.frames[nomFrame1].document.close();
    } else alert("Frame non trouvée : "+nomFrame1);
}

function getXhrObject() {
    if(window.XMLHttpRequest) // Firefox
	return new XMLHttpRequest();
    else if(window.ActiveXObject) // Internet Explorer
	return new ActiveXObject("Microsoft.XMLHTTP");
    else {
	alert("Votre navigateur ne supporte pas les objets XMLHTTPRequest...");
	return null;
    }
}

/* copie de serialize pour éviter le charger le javascript de mozile si non nécessaire */
serialize = function(node) {
	if(!node) return null;
	if(node.xml) return node.xml;
	else if(window.XMLSerializer) {
		var serializer = new XMLSerializer()
		return serializer.serializeToString(node);
	}
	else if(node.outerHTML) return node.outerHTML;
	else if(node.innerHTML) {
		var container = document.createElement("container");
		container.appendChild(node.cloneNode(true));
		return container.innerHTML;
	}
	else {
		alert("mozile.xml.serialize", "No XML serialization technique avaliable in this browser.");
		return null;
	}
}

/* Permet de récupérer le noeud form contenant le bouton
   passé en paramètre
*/
function getFormParent(bouton) {
    var noeud = bouton.parentNode;
    while ( noeud && noeud.tagName.toLowerCase()!="form") {
	noeud=noeud.parentNode;
    }
    return noeud;
}

function getElementEditable(e)
{
	var tab = [];
	var dnl = e.getElementsByTagName("div") ;
	for(i = 0; i < dnl.length; i++)
	    {
		var node = dnl.item(i);
		if (node.getAttribute("contentEditable")=="true")
		    tab.push(node);
	    }
	var dnl = e.getElementsByTagName("simpletexte") ;
	for(i = 0; i < dnl.length; i++)
	    {
		var node = dnl.item(i);
		//if (node.getAttribute("contentEditable")=="true")
		tab.push(node);
	    }
	return tab;
}

function traitementCaractèresSpéciaux(content) {
	content = content.replace(/&/g, "&amp;");
	content = content.replace(/</g, "&lt;");
	content = content.replace(/>/g, "&gt;");
	return content;
}

var separateur = "";

/* pour récupérer la chaine réponse qui sera soumise par le
   formulaire passé en paramètre
*/
function collectFormulaire (formulaire) {
    //var formulaire = document.forms[nomFormulaire];
    var elmts = formulaire.elements;
    var nbrElmt = elmts.length;
    var texte="";
    separateur = "";
    for (var i=0; i<nbrElmt; i++) {
	var typeElmt = elmts[i].type;
	var nameElmt = elmts[i].name;
	var valueElmt = elmts[i].value;
	var repElmt = elmts[i].name+"/"+elmts[i].type;
	if (typeElmt=='select-one') {
	    var no = elmts[i].selectedIndex;
	    texte+=nomVal(nameElmt, elmts[i].options[no].value);
	} else if (typeElmt=='select-multiple') {
	    var no = elmts[i].selectedIndex;
	    if (no!=-1) {
		var lstSel = "";
		for (var j=0; j<elmts[i].options.length; j++){
		    if (elmts[i].options[j].selected==true){
			if (lstSel!='') lstSel+=":";
			lstSel+=elmts[i].options[j].value;
		    }
		}
		texte+=nomVal(nameElmt, lstSel);
	    }
	} else if (typeElmt=='checkbox') {
	    /* 
	    // plusieurs éléments peuvent avoir le nême nom
	    // on regarde si le bouton est coché, sinon on n'envoie rien
	    if (elmts[i].checked) {
		texte+=nomVal(nameElmt, valueElmt);
	    }
	    */
	    // fonctionnement modifié
	    // si le bouton est coché on envoie la valeur, sinon on envoie 'off'
	    // (si coché la valeur est "on")
	    if (elmts[i].checked) {
		//texte+=nomVal(nameElmt, valueElmt);
		texte+=nomVal(nameElmt, 'on');
	    } else texte+=nomVal(nameElmt, 'off');
	} else if (typeElmt=='button') {
	    texte+=nomVal(nameElmt, valueElmt);
	} else if (typeElmt=='file') {
	    //texte=texte+"/"+valueElmt;
	} else if (typeElmt=='hidden') {
	    texte+=nomVal(nameElmt, valueElmt);
	} else if (typeElmt=='image') {
	} else if (typeElmt=='password') {
	    texte+=nomVal(nameElmt, valueElmt);
	} else if (typeElmt=='radio') {
	    if (elmts[i].checked) texte+=nomVal(nameElmt, valueElmt);
	} else if (typeElmt=='reset') {
	} else if (typeElmt=='submit') {
	} else if (typeElmt=='text') {
	    texte+=nomVal(nameElmt, traitementCaractèresSpéciaux(valueElmt));
	} else if (typeElmt=='textarea') {
	    texte+=nomVal(nameElmt, traitementCaractèresSpéciaux(elmts[i]));
	}
    }
    var tabElmEdt = getElementEditable(formulaire);
    for (var i=0; i<tabElmEdt.length; i++) {
	texte+=nomVal(tabElmEdt[i].getAttribute("name"),traitementTextArea(tabElmEdt[i]));

    }
    return texte;
}

function traitementTextArea(node) {
    /* correction d'un problème dû à la manière de mozille de mettre
       des éléments de liste hors des paragraphes
    */
    var nom = ""+node.nodeName;
    var nouvDiv;
    var avant=serialize(node);
    if (node.nodeName=='DIV') {
	var el = node.firstChild;
	var lastEl = null;
	nouvDiv = node.cloneNode(false);
	while (el!=null) {
	    if (el.nodeType!=1 || (el.nodeType==1 && el.nodeName!='P')) {
		if (lastEl==null) {
		    lastEl=document.createElement('P');
		    nouvDiv.appendChild(lastEl);
		}
		lastEl.appendChild(el.cloneNode(true));
	    } else {
		lastEl=el.cloneNode(true);
		nouvDiv.appendChild(lastEl);
	    }
	    el=el.nextSibling;
	}
    } else nouvDiv=node;
    //alert(avant+"==================\j======="+serialize(nouvDiv));
    return serialize(nouvDiv);
}

function nomVal(nom, valeur) {
    var res = separateur+nom+"="+encodeURIComponent(valeur);
    if (mode=='display')
	res = "\n"+separateur+nom+"="+valeur;
    else
	res = separateur+nom+"="+encodeURIComponent(valeur);
    separateur="&";
    return res;
}

/* soumet le contenu du formulaire et renvoie la réponse obtenue
 */
function submitFormulaire(formulaire) {
    var content = collectFormulaire(formulaire);
    var xhr_object = getXhrObject();
    if (mode=='display') {
	alert(content);
    } else {
    if(xhr_object==null) {
	return "<html><body><h1>Votre navigateur ne supporte pas les objets XMLHTTPRequest...</h1></body></html>";
    }
    var location = formulaire.action;
    xhr_object.open("POST", location, false);
    xhr_object.setRequestHeader("Content-type", "application/x-www-form-urlencoded"); 
    xhr_object.send(content);
    var réponse = xhr_object.responseText;
    return réponse;
    }
}

function submitFormulaireXML(formulaire) {
    var content = collectFormulaire(formulaire);
    var xhr_object = getXhrObject();

    if(xhr_object==null) {
	return "<html><body><h1>Votre navigateur ne supporte pas les objets XMLHTTPRequest...</h1></body></html>";
    }
    var location = formulaire.action;
    //    xhr_object.onreadystatechange=stateChanged;
    xhr_object.open("POST", location, false);
    //xhr_object.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhr_object.setRequestHeader("Content-type", "application/x-www-form-urlencoded"); 
    xhr_object.send(content);
    if (xhr_object.responseXML!=null) return xhr_object.responseXML.documentElement;
    else return xhr_object.responseText;
}

// ===============================================================
//
// Fonctions utilisables dans un form d'une page html
//
// ===============================================================
// soumettre le formulaire contenant le bouton, résultat dans la 
// frame1 et reload frame2
function submitFrame1ReloadFrame2bis(bouton, nomFrame1, nomFrame2) {
    var eltForm = getFormParent(bouton);
    var réponse = submitFormulaireXML(eltForm);
    //    alert(réponse);
    //rechargerFrame(nomFrame1);
    //ecrireDocHtmlDansFrame(nomFrame1);
}

function submitFrame1ReloadFrame2(bouton, nomFrame1, nomFrame2) {
    var eltForm = getFormParent(bouton);
    var réponse = submitFormulaireXML(eltForm);
    //alert(réponse);
    if (publitool_saveState) publitool_saveState();
    frm1 = parent.frames[nomFrame1];
    frm2 = parent.frames[nomFrame2];
    doc1=frm1.document.documentElement;
    //doc1.innerHTML = réponse.innerHTML;
    doc1.innerHTML = "";
    //frm1.document.open("text/html","replace");
    rechargerFrame(nomFrame1);
    rechargerFrame(nomFrame2);
    
    /*
    noeud = frm1.document.childNodes[0];
    while (noeud.hasChildNodes()) {
	noeud.removeChild(noeud.childNodes[0]);
    }
    alert(réponse);
    noeudrep = réponse.childNodes[0];
    while (noeudrep.hasChildNodes()) {
	alert("noeud "+noeudrep.childNodes[0].innerHTML);
	noeud.appendChild(noeudrep.removeChild(noeudrep.childNodes[0]));
    }
     
    alert("cleared");
    */

     /*
   if (mode=="display") {
	alert(content);
    } else {
	if (!frm2) {
	    alert("pas de frame "+nomFrame2);
	}
	if (!frm1) {
	    alert("pas de frame "+nomFrame1);
	}
	if (publitool_saveState) publitool_saveState();
	//rechargerFrame(nomFrame2);
	alert(frm1);
	//frm2.location.reload();
	//ecrireDocHtmlDansFrame(nomFrame1, réponse);
	//frm1.document.open("text/html","replace");
	frm1.document.write(réponse);
	frm1.document.close();
	alert("c'est fait");
    }
    */
}

function submitFormIdAndLoad(idForm) {
    var eltForm = document.getElementById(idForm);
    var reponse = submitFormulaire(eltForm);
   if (mode=="display") {
	alert(content);
    } else {
	if (publitool_saveState) publitool_saveState();
	//document.location.reload();
	var letitre = reponse.indexOf("<title>ERR-PUBLITOOL");
	if (reponse.indexOf("<title>ERR-PUBLITOOL")!=-1) {
	    //alert("Erreur "+reponse);
	    var winErr = window.open("", "Erreur PubliTool", "width=800, height=600");
	    winErr.document.open();
	    winErr.document.write(reponse);
	    winErr.document.close();
	} else {
	    document.open("text/html","replace");
	    document.write(reponse);
	    document.close();
	}
    }
}

function submitAndLoad(bouton) {
    var eltForm = getFormParent(bouton);
    var reponse = submitFormulaire(eltForm);
   if (mode=="display") {
	alert(content);
    } else {
	if (publitool_saveState) publitool_saveState();
	//document.location.reload();
	var letitre = reponse.indexOf("<title>ERR-PUBLITOOL");
	if (reponse.indexOf("<title>ERR-PUBLITOOL")!=-1) {
	    //alert("Erreur "+reponse);
	    var winErr = window.open("", "Erreur PubliTool", "width=800, height=600");
	    winErr.document.open();
	    winErr.document.write(reponse);
	    winErr.document.close();
	} else {
	    document.open("text/html","replace");
	    document.write(reponse);
	    document.close();
	}
    }
}

function submitAndBack(bouton) {
    var eltForm = getFormParent(bouton);
    var reponse = submitFormulaire(eltForm);
   if (mode=="display") {
	alert(content);
    } else {
	if (publitool_saveState) publitool_saveState();
	//document.location.reload();
	var letitre = reponse.indexOf("<title>ERR-PUBLITOOL");
	if (reponse.indexOf("<title>ERR-PUBLITOOL")!=-1) {
	    //alert("Erreur "+reponse);
	    var winErr = window.open("", "Erreur PubliTool", "width=800, height=600");
	    winErr.document.open();
	    winErr.document.write(reponse);
	    winErr.document.close();
	} else {
	    history.back();
	}
    }
}

function submitAndWrite(bouton, idval) {
    var zoneReponse = idval;
    var eltForm = getFormParent(bouton);
    var reponse = submitFormulaire(eltForm);
   if (mode=="display") {
	alert(content);
    } else {
	if (publitool_saveState) publitool_saveState();
	//document.location.reload();
	var letitre = reponse.indexOf("<title>ERR-PUBLITOOL");
	if (reponse.indexOf("<title>ERR-PUBLITOOL")!=-1) {
	    //alert("Erreur "+reponse);
	    var winErr = window.open("", "Erreur PubliTool", "width=800, height=600");
	    winErr.document.open();
	    winErr.document.write(reponse);
	    winErr.document.close();
	} else {
	    zoneReponse.innerHTML=reponse;
	}
    }
   return false;
}

function displaySubmit(bouton) {
    var saveMode = mode;
    mode="display";
    var eltForm = getFormParent(bouton);
    var content = collectFormulaire(eltForm);
    mode=saveMode;
    alert(content);
}

// ===============================================================
//
// DROP ZONE
//
// ===============================================================

var publitool_tabFiles = [];

function doDragOver(event)
{
  var isFile = event.dataTransfer.types.contains("application/x-moz-file");
  if (isFile) {
      var dt = event.dataTransfer;
      
    event.preventDefault();
  }
}

function dodrop(idDropFileList, event)  
 {  
   var dt = event.dataTransfer;
   handleFiles(idDropFileList, dt.files);
 }  
   
 function razTabFiles(idDropFileList) {
     var d = document.getElementById(idDropFileList);
     publitool_tabFiles = [];
     while (d.hasChildNodes()) {
        d.removeChild(d.firstChild);
    }
 }

function handleFiles(idDropFileList, files) {  
   var list = document.getElementById(idDropFileList);
   while (list.hasChildNodes()) {
        list.removeChild(list.firstChild);
    }  
     //publitool_tabFiles = publitool_tabFiles.concat(files);
     for (var i=0; i < files.length; i++) { 
        publitool_tabFiles[publitool_tabFiles.length] = files[i];
     }
     for (var i=0; i < publitool_tabFiles.length; i++) {  
       var li = document.createElement("li");  
       list.appendChild(li);  
         
       /*       var inputEl = document.createElement("input");
       inputEl.maxlength = "10";
       inputEl.size = "30";
       inputEl.type = "file";
       */
       var info = document.createElement("span");  
       info.innerHTML = publitool_tabFiles[i].name + ": " + publitool_tabFiles[i].size + " bytes ";// + publitool_tabFiles[i].getAsDataURL() ; 
       li.appendChild(info);
       //li.appendChild(inputEl);
     }
     
     
 }

function collectFormulaireDropZone (formulaire) {
    //var formulaire = document.forms[nomFormulaire];
    var elmts = formulaire.elements;
    var nbrElmt = elmts.length;
    var texte="";
    separateur = "---------------------------PubliTool2009--9002looTilbuP";
    for (var i=0; i<nbrElmt; i++) {
	var typeElmt = elmts[i].type;
	var nameElmt = elmts[i].name;
	var valueElmt = elmts[i].value;
	var repElmt = elmts[i].name+"/"+elmts[i].type;
	if (typeElmt=='select-one') {
	    var no = elmts[i].selectedIndex;
	    texte+=nomValDropZone(nameElmt, elmts[i].options[no].value);
	} else if (typeElmt=='select-multiple') {
	    var no = elmts[i].selectedIndex;
	    if (no!=-1) {
		var lstSel = "";
		for (var j=0; j<elmts[i].options.length; j++){
		    if (elmts[i].options[j].selected==true){
			if (lstSel!='') lstSel+=":";
			lstSel+=elmts[i].options[j].value;
		    }
		}
		texte+=nomValDropZone(nameElmt, lstSel);
	    }
	} else if (typeElmt=='checkbox') {
	    // plusieurs éléments peuvent avoir le nême nom
	    // on regarde si le bouton est coché, sinon on n'envoie rien
	    if (elmts[i].checked) {
		texte+=nomValDropZone(nameElmt, valueElmt);
	    }
	} else if (typeElmt=='button') {
	    texte+=nomValDropZone(nameElmt, valueElmt);
	} else if (typeElmt=='file') {
	    //texte=texte+"/"+valueElmt;
	} else if (typeElmt=='hidden') {
	    texte+=nomValDropZone(nameElmt, valueElmt);
	} else if (typeElmt=='image') {
	} else if (typeElmt=='password') {
	    texte+=nomValDropZone(nameElmt, valueElmt);
	} else if (typeElmt=='radio') {
	    if (elmts[i].checked) texte+=nomValDropZone(nameElmt, valueElmt);
	} else if (typeElmt=='reset') {
	} else if (typeElmt=='submit') {
	} else if (typeElmt=='text') {
	    texte+=nomValDropZone(nameElmt, traitementCaractèresSpéciaux(valueElmt));
	} else if (typeElmt=='textarea') {
	    texte+=nomValDropZone(nameElmt, traitementCaractèresSpéciaux(elmts[i]));
	}
    }
    var tabElmEdt = getElementEditable(formulaire);
    for (var i=0; i<tabElmEdt.length; i++) {
	texte+=nomValDropZone(tabElmEdt[i].getAttribute("name"), serialize(tabElmEdt[i]));

    }
    //dropZone
     for (var i=0; i < publitool_tabFiles.length; i++) {  
	 texte+=nomValDropZoneFichier(publitool_tabFiles[i]);
     }
     texte=texte+"--"+separateur+"--\r\n";
    return texte;
}

function nomValDropZone(nom, valeur) {
    var res = "--"+separateur+"\r\n"
	+"Content-Disposition: form-data; name=\""
	+nom+"\"\r\n\r\n"+encodeURIComponent(valeur)+"\r\n";
    return res;
}

function nomValDropZoneFichier(file) {
    var dataURL = file.getAsDataURL();
    var pos = dataURL.indexOf(";");
    var type = dataURL.substr(5, pos-5);
    pos = dataURL.indexOf(",")+1;
    var dataBase64 = dataURL.substr(pos);
    //alert(type+"\n"+dataBase64);
    var res = "--"+separateur+"\r\n"
	+"Content-Disposition: form-data; name=\""
	+file.name+"\"; filename=\""+file.name+"\"\r\n"
	+"Content-Type: "+type+"\r\n"
	+"Content-Transfer-Encoding: base64"+"\r\n\r\n"
	+dataBase64+"\r\n\r\n";
    return res;
}

function submitFormulaireAvecFichiers(idDropFileList, formulaire) {
    var content = collectFormulaireDropZone(formulaire);
    var xhr_object = getXhrObject();

    if(xhr_object==null) {
	return "<html><body><h1>Votre navigateur ne supporte pas les objets XMLHTTPRequest...</h1></body></html>";
    }
    var location = formulaire.action;
    xhr_object.open("POST", location, false);
    xhr_object.setRequestHeader("Content-type", "multipart/form-data; boundary="+separateur); 
    xhr_object.setRequestHeader("Content-Length", content.length); 
    xhr_object.send(content);
    var réponse = xhr_object.responseText;
    return réponse;
}

function submitFormIdAndLoadAvecFichiers(idDropFileList, idForm) {
    var eltForm = document.getElementById(idForm);
    var reponse = submitFormulaireAvecFichiers(idDropFileList, eltForm);
   if (mode=="display") {
	alert(content);
    } else {
	if (publitool_saveState) publitool_saveState();
	//document.location.reload();
	var letitre = reponse.indexOf("<title>ERR-PUBLITOOL");
	if (reponse.indexOf("<title>ERR-PUBLITOOL")!=-1) {
	    //alert("Erreur "+reponse);
	    var winErr = window.open("", "Erreur PubliTool", "width=800, height=600");
	    winErr.document.open();
	    winErr.document.write(reponse);
	    winErr.document.close();
	} else {
	    document.open("text/html","replace");
	    document.write(reponse);
	    document.close();
	}
    }
}

function submitAndLoadAvecFichiers(idDropFileList, bouton) {
    var eltForm = getFormParent(bouton);
    var reponse = submitFormulaireAvecFichiers(idDropFileList, eltForm);
   if (mode=="display") {
	alert(content);
    } else {
	if (publitool_saveState) publitool_saveState();
	//document.location.reload();
	var letitre = reponse.indexOf("<title>ERR-PUBLITOOL");
	if (reponse.indexOf("<title>ERR-PUBLITOOL")!=-1) {
	    //alert("Erreur "+reponse);
	    var winErr = window.open("", "Erreur PubliTool", "width=800, height=600");
	    winErr.document.open();
	    winErr.document.write(reponse);
	    winErr.document.close();
	} else {
	    document.open("text/html","replace");
	    document.write(reponse);
	    document.close();
	}
    }
}

function submitAndReLoadAvecFichiers(idDropFileList, bouton) {
    var eltForm = getFormParent(bouton);
    var reponse = submitFormulaireAvecFichiers(idDropFileList, eltForm);
   if (mode=="display") {
	alert(content);
    } else {
	if (publitool_saveState) publitool_saveState();
	//document.location.reload();
	var letitre = reponse.indexOf("<title>ERR-PUBLITOOL");
	if (reponse.indexOf("<title>ERR-PUBLITOOL")!=-1) {
	    //alert("Erreur "+reponse);
	    var winErr = window.open("", "Erreur PubliTool", "width=800, height=600");
	    winErr.document.open();
	    winErr.document.write(reponse);
	    winErr.document.close();
	} else {
	    document.location.reload();
	}
    }
}


// ===============================================================
//
// Fonctions utilisables dans un bouton d'une page html
//
// ===============================================================

// Charger la page courante avec la même url et
// les paramètres fournis

function rechargerAvecParam(param){
    var location = self.location.href;
    var i = location.indexOf("?", 0);
    location = location.substring(0,i);
    self.location.href=location+"?"+param;
}

function recharger(){
    self.location.reload();
}

function chargerURL(url){
    self.location.href=url
}

function chargerURLsansHistorique(noeud) {
    location.replace(noeud.getAttribute("href"));
    return false;
}

function chargerStrURLsansHistorique(strUrl) {
    location.replace(strUrl);
    return false;
}


