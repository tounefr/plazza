<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN">

<!--
/**************************************/
 *     Createur : F. Sagez	      *	
 *     Date de Creation : 26/09/02    *	
 *     Date de Mise a jour : 26/09/02 *
 *   Nom du fichier : PlayModule.php3 *	
/**************************************/
-->

<HTML> 
<HEAD><TITLE> Modules du MjjPlayer </TITLE>
<!-- Pour moteur de recherche -->
<META NAME="AUTHOR"
      CONTENT="Frederic Sagez">
<META NAME="KEYWORDS"
      CONTENT="module, modules, players de modules, Modplug, MOD, S3M, XM, DTM, IT, MJJ, MJJPROD, MICKAEL JACKSON, STALIVE, SST IS A J*RK">
</HEAD>
<script TYPE="text/javascript" LANGUAGE=JAVASCRIPT>
<!-- Supprime bandeau publicitaire chez.com
if (top.frames.length!=0)
window.top.document.body.rows = "0, *"
// -->
</script>

<BODY BGCOLOR=black TEXT=white BACKGROUND="Player/Images/FondPlayerMod.gif" LINK="yellow">
<BR><CENTER>
<TABLE CELLPADDING="2" CELLSPACING="2" BORDER="2">
<TR>
	<TD BGCOLOR="gray"><FONT face="Verdana, Arial, Helvetica, sans-serif" size="6">&nbsp;<?php echo $NomModule ?>&nbsp;</FONT></TD>
</TR></TABLE>
</CENTER><BR><BR>

<!-- Ecoute d'un fichier MOD zippé avec MOD Plugin -->
<?php
if($NomModule && file_exists("Player/Musiques/Modules/".$NomModule)) {
?>
<P><center>
<IMG SRC="Player/Images/ENgauche.gif" width="60" height="105">
<EMBED type="audio/x-zipped-mod" 
       	src="Player/Musiques/Modules/<?php echo $NomModule ?>"
       	volume="100"
	loop="true"
	controls="stereo"
	title="<?php echo $NomModule ?>"
	bgcolor="#RRGGBB"
	width="336" height="48">
<IMG SRC="Player/Images/ENdroite.gif" width="60" height="107"><P>
<IMG SRC="Player/Images/PlayMod.gif" width="22" height="14"><FONT face="Verdana, Arial, Helvetica, sans-serif" size="2">&nbsp;Cliquer sur le bouton lecture pour écouter le module.</FONT>
<?php
} // fin du if
else echo "<P><center><B><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">AUCUN MODULE SPECIFIE POUR LA LECTURE !</B></font></center></P>";
?>
<BR><BR><A HREF="MjjPlayer02.html#MODULES">
<P ALIGN=center>
<img src="../Images/Retour.gif" border="0">
</A>

</BODY>
</HTML>
<!-- Begin Nedstat Basic code -->
<!-- Title:  Page Personnelle de FrEd! -->
<!-- URL: http://www.chez.com/freddo -->
<script language="JavaScript" type="text/javascript" src="http://m1.nedstatbasic.net/basic.js">
</script>
<script language="JavaScript" type="text/javascript" >
<!--
  nedstatbasic("ACR+YwhOTRbPqbWD7/usbnEv8brA", 0);
// -->
</script>
<noscript>
<a target="_blank" href="http://v1.nedstatbasic.net/stats?ACR+YwhOTRbPqbWD7/usbnEv8brA"><img
src="http://m1.nedstatbasic.net/n?id=ACR+YwhOTRbPqbWD7/usbnEv8brA"
border="0" nosave width="18" height="18"
alt="Nedstat Basic - Free web site statistics"></a>
<!-- End Nedstat Basic code -->
<A target="

