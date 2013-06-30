<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

<xsl:template match="/">
<html>
<body>
<h3><xsl:value-of select="jcsc/package"/></h3>
<h1><xsl:value-of select="jcsc/class"/></h1>

<table CELLPADDING="1" CELLSPACING="1" BORDER="0" WIDTH="100%">
  <tr>
    <td VALIGN="top" WIDTH="40%" ALIGN="left" BGCOLOR="#ffffcc">Author</td>
    <td VALIGN="top" WIDTH="60%" BGCOLOR="#ccccff" ALIGN="left">
      <b><xsl:value-of select="jcsc/author"/></b>
    </td>
  </tr>
  <tr>
    <td VALIGN="top" WIDTH="40%" ALIGN="left" BGCOLOR="#ffffcc">Violation Count</td>
    <td VALIGN="top" WIDTH="60%" BGCOLOR="#ccccff" ALIGN="left">
      <b><xsl:value-of select="jcsc/count"/></b>
    </td>
  </tr>
  <tr>
    <td VALIGN="top" WIDTH="40%" ALIGN="left" BGCOLOR="#ffffcc">NCSS Count</td>
    <td VALIGN="top" WIDTH="60%" BGCOLOR="#ccccff" ALIGN="left">
      <b><xsl:value-of select="jcsc/ncss"/></b>
    </td>
  </tr>
</table>

<p></p>

<table CELLPADDING="1" CELLSPACING="1" BORDER="0" WIDTH="100%">
  <tr>
    <td VALIGN="top" WIDTH="3%" BGCOLOR="#ccccff" ALIGN="center"><b>L#</b></td>
    <td VALIGN="top" WIDTH="3%" BGCOLOR="#ccccff" ALIGN="center"><b>C#</b></td>
    <td VALIGN="top" BGCOLOR="#ccccff" ALIGN="center"><B>Violation Message</B></td>
  </tr>
  <xsl:for-each select="jcsc/violation">
  <tr>
    <td VALIGN="top" WIDTH="3%" ALIGN="center" BGCOLOR="#ffffcc"><xsl:value-of select="line"/></td>
    <td VALIGN="top" WIDTH="3%" ALIGN="center" BGCOLOR="#ffffcc"><xsl:value-of select="column"/></td>
    <td VALIGN="top" BGCOLOR="#ffcccc"><xsl:value-of select="message"/></td>
  </tr>
  </xsl:for-each>
</table>
</body>
</html>
</xsl:template>
</xsl:stylesheet>
