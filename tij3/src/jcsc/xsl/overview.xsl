<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

<xsl:template match="/">
<html>
<head>
  <title>JCSC Overview</title>
</head>
<body>   

<table cellpadding="0" cellspacing="0" border="0" width="100%">
<tbody>
  <tr>
    <td bgcolor="#ccccff" align="center" valign="center"><font color="#ffffff"><b><h1>JCSC</h1></b></font></td>
    <td bgcolor="#ccccff" align="right" valign="bottom"><font color="#ffffff"><b><i>Check and feel better about your code!</i></b></font></td>
  </tr>
</tbody>
</table>

<p></p>

<table cellpadding="0" cellspacing="0" border="0" width="100%">
  <tr>
    <td align="left"><h2>Overview</h2></td>
    <td align="right"><h4><xsl:value-of select="jcsc/overview/timestamp"/></h4></td>
  </tr>
</table>

<table cellpadding="2" cellspacing="2" border="0" width="100%">
   <tbody>
     <tr>
       <td valign="top" width="50%" bgcolor="#ccccff"><b>Package Count</b></td>
       <td valign="top" bgcolor="#ffffcc"><b><xsl:value-of select="jcsc/overview/packagecount"/></b></td>
     </tr>
     <tr>
       <td valign="top" width="50%" bgcolor="#ccccff"><b>Class Count</b></td>
       <td valign="top" bgcolor="#ffffcc"><b><xsl:value-of select="jcsc/overview/classcount"/></b></td>
     </tr>
     <tr>
       <td valign="top" width="50%" bgcolor="#ccccff"><b>Total Violations Count</b></td>
       <td valign="top" bgcolor="#ffffcc"><b><xsl:value-of select="jcsc/overview/violationscount"/></b></td>
     </tr>
     <tr>
       <td valign="top" width="50%" bgcolor="#ccccff"><b>Avergage per Class</b></td>
       <td valign="top" bgcolor="#ffffcc"><b><xsl:value-of select="jcsc/overview/avgperclass"/></b></td>
     </tr>
     <tr>
       <td valign="top" width="50%" bgcolor="#ccccff"><b>Total NCSS Count</b></td>
       <td valign="top" bgcolor="#ffffcc"><b><xsl:value-of select="jcsc/overview/ncsscount"/></b></td>
     </tr>
     <tr>
       <td valign="top" width="50%" bgcolor="#ccccff"><b>Avergage per NCSS</b></td>
       <td valign="top" bgcolor="#ffffcc"><b><xsl:value-of select="jcsc/overview/avgperncss"/></b></td>
     </tr>
     <tr>
       <td valign="top" width="50%" bgcolor="#ccccff"><b>Unit Test Class Count</b></td>
       <td valign="top" bgcolor="#ffffcc"><b><xsl:value-of select="jcsc/overview/unittestclasscount"/></b></td>
     </tr>
  </tbody> 
</table>

<h2>Worst Classes</h2>
<table cellpadding="2" cellspacing="2" border="0" width="100%">
   <tbody>
     <tr>
       <td valign="top" width="65%" bgcolor="#ccccff"><b>Class</b></td>
       <td valign="top" width="10%" bgcolor="#ccccff"><b>Count</b></td>
       <td valign="top" width="25%" bgcolor="#ccccff"><b>Author</b></td>
     </tr>
     <xsl:for-each select="jcsc/overview/worstclasses/worst">
       <xsl:if test="count &gt; 0.0">
         <tr>
           <td valign="top" bgcolor="#ffffcc">
           <b>
           <xsl:element name="a">
             <xsl:attribute name="href"><xsl:value-of select="class"/>.xml</xsl:attribute>
             <xsl:attribute name="target">classFrame</xsl:attribute>      
             <xsl:value-of select="class"/>
           </xsl:element>
           </b>
           </td>
           <td valign="top" bgcolor="#ffcccc"><b><xsl:value-of select="count"/></b></td>
           <td valign="top" bgcolor="#ccccff"><b><xsl:value-of select="author"/></b></td>
         </tr>
       </xsl:if>
     </xsl:for-each>
  </tbody> 
</table>

<hr width="100%" size="2"></hr> 

<div align="center"> 
<body>
(c) 1999-2002 by Ralph Jocham (<a href="mailto:rjocham72@netscape.net">rjocham72@netscape.net</a>)<br></br><a href="http://jcsc.sourceforge.net">JCSC</a> is released under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public License</a>
</body>
</div>

</body>
</html>
</xsl:template>
</xsl:stylesheet>
