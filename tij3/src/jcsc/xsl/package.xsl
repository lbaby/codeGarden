<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

<xsl:template match="jcsc/classlist">
<html>
  <xsl:apply-templates/>
</html>
</xsl:template>

<xsl:template match="package">   
  <h4><xsl:value-of select="."/></h4>
  <xsl:apply-templates select="classes" />
</xsl:template>

<xsl:template match="classes">
   <xsl:apply-templates select="class"/>
</xsl:template>

<xsl:template match="class">
  <xsl:element name="a">
    <xsl:attribute name="href"><xsl:value-of select="."/>.xml</xsl:attribute>
    <xsl:attribute name="target">classFrame</xsl:attribute>      
    <xsl:value-of select="."/>
    <br/>
  </xsl:element>
</xsl:template>

</xsl:stylesheet>
