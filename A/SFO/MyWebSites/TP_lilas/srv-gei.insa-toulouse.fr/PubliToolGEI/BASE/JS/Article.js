
function chargerURLsansHistorique(noeud) {
    location.replace(noeud.getAttribute("href"));
    return false;
}

function chargerStrURLsansHistorique(strUrl) {
    location.replace(strUrl);
    return false; 
}

function chargerURLavecHistorique(noeud) {
    location.replace(noeud.getAttribute("href"));
    return true;
}

function chargerStrURLavecHistorique(strUrl) {
    location.replace(strUrl);
    return true;
}
  