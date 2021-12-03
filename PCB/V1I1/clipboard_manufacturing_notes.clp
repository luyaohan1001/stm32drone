; Allegro sub-drawing file
; Created by OrCAD PCB Designer Standard; version= 17.2-2016 S025

_clp_lay_drw = axlDesignType(nil)
_clp_sym = nil
_clp_pbuf  = nil
_clp_cinfo = make_clp_coord_info()
_clp_cinfo->f_rotation = 0.0
_clp_cinfo->l_origin = '(0.0 0.0)
_clp_text_orient = make_axlTextOrientation()
_clp_pin_text = make_axlPinText()
_clp_cinfo->t_from_units = "millimeters"
_clp_cinfo->t_to_units = car(axlDBGetDesignUnits())
_clp_cinfo->preserve_shape_net = nil
_clp_cinfo->preserve_via_net = nil
_clp_cinfo->snapToObject = nil
_clp_cinfo->createNCLayers = nil
_clp_group_info = make_clp_group_info()
_clp_cinfo->group_info = _clp_group_info
_clp_accuracy =3
_clpCheckAccuracy(_clp_accuracy _clp_cinfo->t_from_units	 	_clp_cinfo->t_to_units)
(putprop _clp_cinfo (list (_clpAdjustPt -28.2:-74.25 _clp_cinfo)	
	(_clpAdjustPt 324.4:158.4 _clp_cinfo)) 'l_extents)
(putprop _clp_cinfo (_clpAdjustPt '(0.0 0.0) _clp_cinfo) 'l_zeropt)
(unless (_clpSelectRotOrg _clp_cinfo)
	(error "CANCEL"))
_clp_clip_prop_value = _clpGetClipPropValue()

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "- PANELIZE PCBS INTO PANEL 3 x 3 (3 COLUMNS AND 3 ROWS)" 
	(_clpAdjustPt 144:102 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "- FIDUCIAL DIAMETER 1-1.5MM, SOLDER MASK OPENING AT LEAST 1MM GREATER THAN FIDUCIAL" 
	(_clpAdjustPt 142:90 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "- MINIMUM 4MM DISTANCE FROM THE PANEL EDGE" 
	(_clpAdjustPt 142:86 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "- 3 FIDUCIALS SHOULD LIE ON TWO LINES THAT INTERSECT AT A RIGHT ANGLE" 
	(_clpAdjustPt 142:82 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "- PLACE ONE FIDUCIAL INTO EACH PANEL CORNER" 
	(_clpAdjustPt 142:78 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

printf(" 10 percent completed")
newline()

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "- PLACE FOUR FIDUCIALS ON THE TOP LAYER AND FOUR ON THE BOTTOM LAYER" 
	(_clpAdjustPt 142:74 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "- REQUIRED: KEEP COPPER THICKNESS OF L1 LAYER AT LEAST 35um, OTHER LAYERS AT LEAST 18um" 
	(_clpAdjustPt 142:62 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "- FINISHED PANEL THICKNESS IS NOT CRITICAL: TO BE APPROXIMATELY 1.6mm" 
	(_clpAdjustPt 142:58 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "- OTHER PARAMETERS OF STACKUP ARE NOT CRITICAL, PCB MANUFACTURER CAN DECIDE." 
	(_clpAdjustPt 142:54 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "Board info" 
	(_clpAdjustPt 138:156 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

printf(" 20 percent completed")
newline()

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "Minimum Track: 200um" 
	(_clpAdjustPt 138:152 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "Minimum Gap: 200um" 
	(_clpAdjustPt 138:148 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "Minimum Through Hole VIA: 0.6mm (pad) / 0.3mm (drill). Drilling: L1-L6" 
	(_clpAdjustPt 138:144 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "1. BOARD FINISH: IMMERSION Au/ELECTROLESS Ni; 0.05-0.12 um GOLD; 3-6um NICKEL" 
	(_clpAdjustPt 138:130 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "2. SOLDER RESIST: APPLY TO BOTH SIDES COLOUR - BLUE" 
	(_clpAdjustPt 138:122 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

printf(" 30 percent completed")
newline()

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "3. COMPONENT IDENT: COLOUR TO BE WHITE" 
	(_clpAdjustPt 138:114 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "4. PANELIZE THE BOARD (9PCS PER PANEL)" 
	(_clpAdjustPt 138:106 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "5. PLACE FIDUCIALS ON THE PANEL STRIPS AS FOLLOWS:" 
	(_clpAdjustPt 138:94 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "6. STACKUP INFORMATION:" 
	(_clpAdjustPt 138:66 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

printf(" 40 percent completed")
newline()

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "6" )
_clp_dbid = (_clpDBCreateText "V1I1" 
	(_clpAdjustPt 84:-42 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "Designed by FEDEVEL" 
	(_clpAdjustPt 42:-54 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "www.fedevel.com" 
	(_clpAdjustPt 42:-58 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

printf(" 50 percent completed")
newline()

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "6" )
_clp_dbid = (_clpDBCreateText "ISL6236A Project" 
	(_clpAdjustPt -22:-42 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "Copyright 2017" 
	(_clpAdjustPt -22:-54 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "FEDEVEL" 
	(_clpAdjustPt -22:-58 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "Contact: robert.feranec@fedevel.com" 
	(_clpAdjustPt -22:-70 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

printf(" 60 percent completed")
newline()

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "Files:" 
	(_clpAdjustPt -28:154 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "01-TOP_OVERLAY.art - Top Overlay" 
	(_clpAdjustPt -28:150 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

printf(" 70 percent completed")
newline()

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "02-TOP_PASTE.art - Top Paste" 
	(_clpAdjustPt -28:146 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "03-TOP_SOLDER.art - Top Solder" 
	(_clpAdjustPt -28:142 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "04-L1.art - Layer 1" 
	(_clpAdjustPt -28:138 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "05-L2.art - Layer 2" 
	(_clpAdjustPt -28:134 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "06-L3.art - Layer 3" 
	(_clpAdjustPt -28:130 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

printf(" 80 percent completed")
newline()

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "07-L4.art - Layer 4" 
	(_clpAdjustPt -28:126 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "08-L5.art - Layer 5" 
	(_clpAdjustPt -28:122 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "09-L6.art - Layer 6" 
	(_clpAdjustPt -28:118 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "10-BOTTOM_SOLDER.art - Bottom Solder" 
	(_clpAdjustPt -28:114 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "11-BOTTOM_PASTE.art - Bottom Paste" 
	(_clpAdjustPt -28:110 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

printf(" 90 percent completed")
newline()

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "12-BOTTOM_OVERLAY.art - Bottom Overlay" 
	(_clpAdjustPt -28:106 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "13-MECH_DRAWING.art - Mechanical Drawing" 
	(_clpAdjustPt -28:102 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "14-MFG_NOTES.art - Manufacturing Notes" 
	(_clpAdjustPt -28:98 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

(_clpInitTextOrientation _clp_text_orient "LEFT" nil _clp_cinfo->f_rotation + 0.000 "7" )
_clp_dbid = (_clpDBCreateText "15-BOARD_OUTLINE.art - Board Outline" 
	(_clpAdjustPt -28:94 _clp_cinfo)  _clp_text_orient 
	"MANUFACTURING/MFG_NOTES" _clp_sym)

_clp_dbid = car(_clp_dbid)
when(_clp_dbid _clpDBAddProp( _clp_dbid list(
	)))

_clp_path  = (_clpPathStart (list (_clpAdjustPt -26:-62 _clp_cinfo))
	(_clpMKSConvert 0.500000 _clp_cinfo->t_from_units _clp_cinfo->t_to_units))
_clp_path  = (_clpPathLine _clp_path (_clpMKSConvert 0.500000 _clp_cinfo->t_from_units
	_clp_cinfo->t_to_units) (_clpAdjustPt -26:-74 _clp_cinfo))
_clp_path  = (_clpPathLine _clp_path (_clpMKSConvert 0.500000 _clp_cinfo->t_from_units
	_clp_cinfo->t_to_units) (_clpAdjustPt 110:-74 _clp_cinfo))
_clp_path  = (_clpPathLine _clp_path (_clpMKSConvert 0.500000 _clp_cinfo->t_from_units
	_clp_cinfo->t_to_units) (_clpAdjustPt 110:-62 _clp_cinfo))
_clpPl = list(
	list("CLIP_DRAWING" _clp_clip_prop_value))
_clp_dbid = _clpDBCreatePath(_clp_path "MANUFACTURING/MFG_NOTES" 'line _clp_sym _clpPl)
_clpPl = nil

_clp_path  = (_clpPathStart (list (_clpAdjustPt -26:-46 _clp_cinfo))
	(_clpMKSConvert 0.500000 _clp_cinfo->t_from_units _clp_cinfo->t_to_units))
_clp_path  = (_clpPathLine _clp_path (_clpMKSConvert 0.500000 _clp_cinfo->t_from_units
	_clp_cinfo->t_to_units) (_clpAdjustPt -26:-62 _clp_cinfo))
_clp_path  = (_clpPathLine _clp_path (_clpMKSConvert 0.500000 _clp_cinfo->t_from_units
	_clp_cinfo->t_to_units) (_clpAdjustPt 110:-62 _clp_cinfo))
_clp_path  = (_clpPathLine _clp_path (_clpMKSConvert 0.500000 _clp_cinfo->t_from_units
	_clp_cinfo->t_to_units) (_clpAdjustPt 110:-46 _clp_cinfo))
_clpPl = list(
	list("CLIP_DRAWING" _clp_clip_prop_value))
_clp_dbid = _clpDBCreatePath(_clp_path "MANUFACTURING/MFG_NOTES" 'line _clp_sym _clpPl)
_clpPl = nil

_clp_path  = (_clpPathStart (list (_clpAdjustPt -26.1:-45.9 _clp_cinfo))
	(_clpMKSConvert 0.500000 _clp_cinfo->t_from_units _clp_cinfo->t_to_units))
_clp_path  = (_clpPathLine _clp_path (_clpMKSConvert 0.500000 _clp_cinfo->t_from_units
	_clp_cinfo->t_to_units) (_clpAdjustPt 109.9:-45.9 _clp_cinfo))
_clp_path  = (_clpPathLine _clp_path (_clpMKSConvert 0.500000 _clp_cinfo->t_from_units
	_clp_cinfo->t_to_units) (_clpAdjustPt 110:-46 _clp_cinfo))
_clp_path  = (_clpPathLine _clp_path (_clpMKSConvert 0.500000 _clp_cinfo->t_from_units
	_clp_cinfo->t_to_units) (_clpAdjustPt 110:-32 _clp_cinfo))
_clp_path  = (_clpPathLine _clp_path (_clpMKSConvert 0.500000 _clp_cinfo->t_from_units
	_clp_cinfo->t_to_units) (_clpAdjustPt -26:-32 _clp_cinfo))
_clp_path  = (_clpPathLine _clp_path (_clpMKSConvert 0.500000 _clp_cinfo->t_from_units
	_clp_cinfo->t_to_units) (_clpAdjustPt -26.1:-32.1 _clp_cinfo))
_clp_path  = (_clpPathLine _clp_path (_clpMKSConvert 0.500000 _clp_cinfo->t_from_units
	_clp_cinfo->t_to_units) (_clpAdjustPt -26.1:-45.9 _clp_cinfo))
_clpPl = list(
	list("CLIP_DRAWING" _clp_clip_prop_value))
_clp_dbid = _clpDBCreatePath(_clp_path "MANUFACTURING/MFG_NOTES" 'line _clp_sym _clpPl)
_clpPl = nil

_clp_path  = (_clpPathStart (list (_clpAdjustPt 36:-46 _clp_cinfo))
	(_clpMKSConvert 0.500000 _clp_cinfo->t_from_units _clp_cinfo->t_to_units))
_clp_path  = (_clpPathLine _clp_path (_clpMKSConvert 0.500000 _clp_cinfo->t_from_units
	_clp_cinfo->t_to_units) (_clpAdjustPt 36:-62 _clp_cinfo))
_clpPl = list(
	list("CLIP_DRAWING" _clp_clip_prop_value))
_clp_dbid = _clpDBCreatePath(_clp_path "MANUFACTURING/MFG_NOTES" 'line _clp_sym _clpPl)
_clpPl = nil

_clp_path  = (_clpPathStart (list (_clpAdjustPt 78:-46 _clp_cinfo))
	(_clpMKSConvert 0.500000 _clp_cinfo->t_from_units _clp_cinfo->t_to_units))
_clp_path  = (_clpPathLine _clp_path (_clpMKSConvert 0.500000 _clp_cinfo->t_from_units
	_clp_cinfo->t_to_units) (_clpAdjustPt 78:-32 _clp_cinfo))
_clpPl = list(
	list("CLIP_DRAWING" _clp_clip_prop_value))
_clp_dbid = _clpDBCreatePath(_clp_path "MANUFACTURING/MFG_NOTES" 'line _clp_sym _clpPl)
_clpPl = nil

printf(" 100 percent completed")
newline()

axlFlushDisplay()
