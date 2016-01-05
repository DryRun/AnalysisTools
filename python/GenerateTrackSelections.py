import os
import sys

#for cut_numberOfContribPixelLayers in [0, 1, 2, -1]:
for cut_numberOfContribPixelLayers in [0, 1, 2]:
    for cut_numberOfPixelHoles in [0, 1]:
        for cut_d0 in ["withBS", "withoutBS"]:
            name = "TrackSelection_pixhits_"
            if cut_numberOfContribPixelLayers >= 0:
                name += str(cut_numberOfContribPixelLayers)
            else:
                name += "IO"
            name += "_pixholes_" + str(cut_numberOfPixelHoles) + "_d0" + cut_d0 + "_7"
            xml_file = open("/global/u2/d/dryu/Luminosity/Code/AnalysisTools/data/TrackSelections/{}.xml".format(name), 'w')
            xml_file.write("<?xml version=\"1.0\"?>\n")
            xml_file.write("<!DOCTYPE selection SYSTEM \"http://www-atlas.lbl.gov/~dryu/Multilepton/selections.dtd\">\n")
            xml_file.write("<selection>\n")
            xml_file.write("\t<author>David Yu</author>\n")
            xml_file.write("\t<name>{}</name>\n\n".format(name))

            # Pixel layer cut
            if cut_numberOfContribPixelLayers >= 0:
                #xml_file.write("\t<cut name=\"MinNPixLayerHits\">\n")
                xml_file.write("\t<cut name=\"MinNPixHits\">\n")
                xml_file.write("\t\t<parameter>{}</parameter>\n".format(cut_numberOfContribPixelLayers))
                xml_file.write("\t</cut>\n")
            else:
                xml_file.write("\t<cut name=\"MinNInnerPixLayerHits\">\n")
                xml_file.write("\t\t<parameter>1</parameter>\n")
                xml_file.write("\t</cut>\n")
                xml_file.write("\t<cut name=\"MinNOuterPixLayerHits\">\n")
                xml_file.write("\t\t<parameter>1</parameter>\n")
                xml_file.write("\t</cut>\n")

            # Pixel hole cut
            xml_file.write("\t<cut name=\"MaxNPixHoles\">\n")
            xml_file.write("\t\t<parameter>{}</parameter>\n".format(cut_numberOfPixelHoles))
            xml_file.write("\t</cut>\n")

            # d0 cut
            if cut_d0 == "withBS":
                xml_file.write("\t<cut name=\"MaxD0Significance\">\n")
                xml_file.write("\t\t<parameter>7</parameter>\n")
                xml_file.write("\t</cut>\n")
            else:
                xml_file.write("\t<cut name=\"MaxD0SignificanceNoBeamspot\">\n")
                xml_file.write("\t\t<parameter>7</parameter>\n")
                xml_file.write("\t</cut>\n")

            # Number of silicon hits
            xml_file.write("\t<cut name=\"MinNSiHits\">\n")
            xml_file.write("\t\t<parameter>9</parameter>\n")
            xml_file.write("\t</cut>\n")

            xml_file.write("</selection>\n")


