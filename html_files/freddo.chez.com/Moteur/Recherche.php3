<!--
/**************************************/
 *     Createur : F. Sagez	      *
 *     Date de Creation : 11/06/01    *
 *     Date de Mise a jour : 03/06/03 *
 *     Nom du fichier : Recherche.php *
/**************************************/
-->
<?php
// Pas de fichier d'indexation
if(!file_exists("index.dbf")) {
  print_header();
  echo("<br><center><b><font face='Verdana' size='2'>La base de données de recherche est introuvable.</b>".
       "<br>Contacter l'<A HREF=\"mailto:freddo@chez.com?Subject=La base de données de recherche est introuvable !!!</font>\">administrateur</A> du site S.V.P.</b></center><BR><BR><BR>");
  print_footer();
  exit;
}
?>

<?php
print_header();
?>

<font face="verdana"><center><TABLE BORDER='1'>
<TR><TD bgcolor='#996699'><font face='Verdana' size='2'>Rechercher sur le site :&nbsp;</font></TD>
<form action="Resultats.php3" method="post">
<TD bgcolor='#663366'><input type="text" name="requete" size="25"></TD>
<TD bgcolor='#996699'>&nbsp;<input type="submit" value="Go !" align="top"></TD>
</form></TR></TABLE></center></font>

<BR><CENTER>
	<P><font face='Verdana' size='2'>Résultat de la recherche sur le site : <B>Taper 
		un mot S.V.P.</B></font></P>
	<BR><BR>
<!--
	<P><FONT face="Verdana, Arial, Helvetica, sans-serif" size="4"><IMG src="../Images/New.gif" width="32" height="21" align="texttop">Jeux 
		et compiles <B>ATARI ST</B> sont référencés sur </FONT><A href="http://atari.games.free.fr/atarist/where_is.php" target="_parent"><IMG src="atari.games.jpg" width="130" height="22" border="1" align="texttop" alt="Base de Donn&eacute;es WHEREIS !"></A></P>
-->
</CENTER>

<?php
print_footer();
?>

<?php

function print_header()
{
 echo("<html>\n<head>\n<title> Rechercher sur le site de Freddo \n</title><meta name=\"index\" content=\"no\"\n");
 echo("<meta name='AUTHOR' content='Frederic Sagez'>\n<meta name='KEYWORDS' content='Atari, Amiga, modules, players de modules, trackers pour modules, samples, songs, modules, ST, Atari ST, Pacifist, TOS, GEM, Capture d'images, schoumi'>\n");
 echo("</head>\n");
 echo("<script TYPE=\"text/javascript\" LANGUAGE=JAVASCRIPT>\n");
 echo("<!-- Supprime bandeau publicitaire chez.com\n");
 echo("if (top.frames.length!=0)\n");
 echo("	window.top.document.body.rows = \"0, *\";\n");
 echo("// -->\n");
 echo("</script>\n");
 echo("\n<body bgcolor='#660099' text='white' background=\"FondMoteur.gif\" link='#3ED4AD' vlink='#3ED4AD' alink='#3ED4AD'>\n");
 echo("\n<CENTER><IMG SRC='MoteurdeRecherche.gif' BORDER='0'></CENTER><BR><BR><BR>");
}

function print_footer()
{
echo("
<BR><CENTER>
    <table width=680 border=1 cellspacing=0 cellpadding=0 bordercolor=\"#333333\" bgcolor='#996699'>
      <tr>
        <td valign=\"middle\" nowrap align=center><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">
        &nbsp;Search Only Word ! ~~~ (c) La Bonne Methode - Avril 2002 ~~~ <A HREF='http://LBM.ifrance.com' TARGET='_blanck'>LBM.ifrance.com</A>
        </td>
      </tr>
    </table></CENTER>
");
 echo("
 <p align=\"center\"><br>
  <br>
  <a href=\"../index2.html\"><img src=\"../Atari/Images/Retour.gif\" width=\"171\" height=\"37\" align=\"middle\" border=\"0\"></a>
  <br>
  <br>
  <br>
  </p>
  </body>
  </html><noscript>
  <A target=\"");
}
?>


