<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

<xsl:template match="/">
<html>
  <h4><a href="overview.xml" target="classFrame">Overview</a></h4>
  <h3>Packages</h3>
  <h4><a href="allclasses.xml" target="packageFrame">All Classes</a></h4>
  <xsl:for-each select="jcsc/packagelist/package">
    <xsl:element name="a">
      <xsl:attribute name="href"><xsl:value-of select="."/>.xml</xsl:attribute>
      <xsl:attribute name="target">packageFrame</xsl:attribute>
      <xsl:value-of select="."/>
    </xsl:element>
    <br></br>
  </xsl:for-each>
</html>
</xsl:template>
</xsl:stylesheet>
