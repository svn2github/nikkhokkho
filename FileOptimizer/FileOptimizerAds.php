<?php
	$iWidth = @filter_var($_GET['w'], FILTER_SANITIZE_NUMBER_INT);
	$iHeight = @filter_var($_GET['h'], FILTER_SANITIZE_NUMBER_INT);
	if ($iHeight == 0)
	{
		$iHeight = 90;
	}
	$iDebug = @filter_var($_GET['d'], FILTER_SANITIZE_NUMBER_INT);
	$sSearch = @filter_var($_GET['q'], FILTER_SANITIZE_STRING);
	

	function GetBanner()	
	{
		global $iWidth, $iHeight;
		static $iCont = 0;
		$iRnd = mt_rand(0, 100);
		$iCont++;

		if ($iRnd < 40)
		{
			//Adsense 728x90
			$sBanner = '<script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script><ins class="adsbygoogle" style="display:inline-block;width:728px;height:90px" data-ad-client="ca-pub-6958213404940013" data-ad-slot="6985177659"></ins><script>(adsbygoogle = window.adsbygoogle || []).push({});</script>';
		}
		else if ($iRnd < 80)
		{
			//ADX
			$sBanner = '<script async="async" src="https://www.googletagservices.com/tag/js/gpt.js"></script><script>var googletag=googletag || {}; googletag.cmd=googletag.cmd || []; googletag.cmd.push(function() { googletag.defineSlot("/360613911/GenericDFP2017", [728, 90], "div-gpt-ad-1506002846364-' . $iCont . '").addService(googletag.pubads()); googletag.pubads().enableSingleRequest(); googletag.enableServices(); });</script><div id="div-gpt-ad-1506002846364-' . $iCont . '" style="height:90px; width:728px;"><script>googletag.cmd.push(function() { googletag.display("div-gpt-ad-1506002846364-' . $iCont . '"); });</script></div>';
		}
		else if ($iRnd < 90)
		{
			//Clicksor
			//$sBanner = '<script type="text/javascript">ad_idzone="1306998"; ad_width="728"; ad_height="90";</script><script type="text/javascript" src="https://ads.exoclick.com/ads.js"></script>';
		}
		else if ($iRnd < 90)
		{
			//Chitika 728x90
			$sBanner = '<script type="text/javascript">( function() { if (window.CHITIKA === undefined) { window.CHITIKA = { \'units\' : [] }; }; var unit = {"calltype":"async[2]","publisher":"guti","width":728,"height":90,"sid":"Chitika Default"}; var placement_id = window.CHITIKA.units.length; window.CHITIKA.units.push(unit); document.write(\'<div id="chitikaAdBlock-\' + placement_id + \'"></div>\');}());</script><script type="text/javascript" src="https://cdn.chitika.net/getads.js" async></script>';
		}
		return($sBanner);
	}
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>FileOptimizer Search: <?php echo @substr($sSearch, 0, 80); ?></title> 
	<meta http-equiv="refresh" content="<?php echo mt_rand(15, 45); ?>"/>
	<meta name="robots" content="none"/>
	<?php
		if ($iDebug === 1)
		{
	?>
			<meta http-equiv="Expires" content="0"/>
		 	<meta http-equiv="Last-Modified" content="0"/>
		 	<meta http-equiv="Cache-Control" content="no-cache, mustrevalidate"/>
		 	<meta http-equiv="Pragma" content="no-cache"/>
	<?php
		}
		$iRnd = mt_rand(0, 100);
		//Taboola
		if ($iRnd > 10)
		{
			?>
			<script type="text/javascript">window._taboola = window._taboola || []; _taboola.push({article:'auto'}); !function (e, f, u, i)
				{
					if (!document.getElementById(i))
					{
						e.async = 1;
						e.src = u;
						e.id = i;
						f.parentNode.insertBefore(e, f);
					}
				}
				(document.createElement('script'), document.getElementsByTagName('script')[0], '//cdn.taboola.com/libtrc/nikkhokkho/loader.js', 'tb_loader_script');
				if(window.performance && typeof window.performance.mark == 'function')
				{
					window.performance.mark('tbl_ic');
				}
			</script>
		<?php
		}
	?>
	<base target="_blank"/>
</head>
	
<body leftmargin=0 topmargin=0 rightmargin=0 bottommargin=0 marginwidth=0 marginheight=0>

<table border=0 cellspacing=0 cellpadding=0 width="100%">
<tr height="<?php echo $iHeight; ?>">
	<?php
		if ($iRnd > 10)
		{
	?>
			<td valign="top"><div id="taboola-below-article-thumbnails"></div><script type="text/javascript">window._taboola = window._taboola || []; _taboola.push({mode: 'thumbnails-a', container: 'taboola-below-article-thumbnails', placement: 'Below Article Thumbnails', target_type: 'mix'});</script></td>
	<?php
		}
		//Taboola
		else
		{
	?>
				<?php
					$iBanners = 6;
					for ($iBanner = 0; $iBanner < $iBanners; $iBanner++)
					{
				?>
						<td valign="top"><?php echo GetBanner(); ?></td>
				<?php
					}
				?>
	<?php
		}
	?>
</tr>
</table>
<br/><br/><br/><br/><br/><br/>
FileOptimizer is an advanced file optimizer featuring a lossless (no quality loss) file size reduction that supports: .3G2, .3GG, .3GP, .7Z, .A, .AAI, .AC, .ACC, .ADP, .AI, .AIR, .APK, .APNG, .APPX, .APR, .ART, .ART, .AVI, .AVS, .BAR, .BMP, .BPG, .BPL, .BSZ, .CBT, .CBZ, .CDR, .CDT, .CHI, .CHM, .CHQ, .CHS, .CHW, .CIN, .CMYK, .CMYKA, .CPL, .CSL, .CSS, .CUR, .DB, .DB, .DCX, .DDS, .DEB, .DES, .DIB, .DLL, .DOC, .DOCM, .DOCX, .DOT, .DOTM, .DOTX, .DPX, .DRV, .DWF, .DWFX, .EAR, .EASM, .EML, .EMLX, .EPDF, .EPDF, .EPRT, .EPUB, .EXE, .FAX, .FAX, .FB2, .FDF, .FITS, .FLA, .FLAC, .FLV, .FPX, .FPX, .FXG, .FXG, .GALLERY, .GALLERYCOLLECTION, .GALLERYITEM, .GIF, .GRAY, .GRS, .GZ, .HDR, .HRZ, .HTM, .HTML, .ICB, .ICL, .ICO, .ICO, .INK, .INLINE, .IPA, .IPK, .IPSW, .ITA, .ITS, .ITZ, .J2C, .J2K, .JAR, .JFI, .JFIF, .JIF, .JNG, .JP2, .JPC, .JPE, .JPEG, .JPG, .JPS, .JPT, .JS, .JSON, .KML, .KMZ, .KMZ, .KSF, .LIB, .LIT, .LUA, .LUAC, .LXF, .LZL, .LZMA, .M4A, .M4B, .M4P, .M4R, .M4V, .MAX, .MBX, .MCE, .MDB, .MDT, .MDZ, .MHT, .MHT, .MHTML, .MHTML, .MIC, .MIF, .MIFF, .MIX, .MIZ, .MK3D, .MKA, .MKS, .MKV, .MMIP, .MNG, .MONO, .MOV, .MP3, .MP4, .MPC, .MPD, .MPEG, .MPG, .MPO, .MPP, .MPP, .MPR, .MPT, .MSC, .MSG, .MSG, .MSI, .MSL, .MSP, .MST, .MSZ, .MTV, .MTW, .MVG, .MVZ, .MZZ, .NAR, .NBK, .NOTEBOOK, .O, .OBJ, .OCX, .ODB, .ODF, .ODG, .ODP, .ODS, .ODT, .OEX, .OGA, .OGG, .OGG, .OGV, .OGX, .OGX, .OLE, .OLE2, .ONE, .OPT, .OSK, .OST, .OTB, .OXPS, .P7, .PALM, .PBM, .PCC, .PCD, .PCDS, .PCL, .PCLS, .PCX, .PDB, .PDF, .PFM, .PFS, .PGM, .PIC, .PICON, .PICT, .PK3, .PNG, .PNM, .PNS, .POTM, .POTX, .PPAM, .PPM, .PPS, .PPSM, .PPSX, .PPT, .PPTM, .PPTX, .PSB, .PSD, .PTIF, .PTIF, .PTIFF, .PTIFF, .PUB, .PUB, .PUZ, .QT, .QWK, .R2SKIN, .RA, .RAM, .RDB, .RFA, .RFG, .RFT, .RGB, .RGBA, .RLL, .RM, .RMSKIN, .RMVB, .RTE, .RV, .RVT, .S3Z, .SCR, .SGI, .SGML, .SLDASM, .SLDDRW, .SLDM, .SLDPRT, .SLDX, .SMIL, .SOU, .SPL, .SPO, .SQLITE, .SQLITE2, .SQLITE3, .STZ, .SUN, .SVG, .SVGZ, .SWC, .SWF, .SYS, .TAR, .TGA, .TGZ, .THM, .TIF, .TIFF, .UYVY, .VBX, .VCARD, .VCF, .VDA, .VDX, .VICAR, .VIFF, .VLT, .VOB, .VSD, .VSS, .VST, .VST, .VSX, .VTX, .WAL, .WAR, .WBA, .WBMP, .WEBA, .WEBM, .WEBP, .WIZ, .WMA, .WMV, .WMZ, .WPS, .WSZ, .X, .XAP, .XBM, .XHTML, .XHTML, .XL, .XLA, .XLAM, .XLC, .XLM, .XLS, .XLSM, .XLSX, .XLTM, .XLTX, .XLW, .XML, .XML, .XMZ, .XNK, .XPI, .XPM, .XPS, .XSF, .XSL, .XSLT, .XSN, .XWD, .YCBR, .YCBRA, .YUB, .Z01, .Z02, .Z03, .Z04, .Z05, .Z06, .Z07, .Z08, .Z09, .Z10, .ZIP, .ZIPX, .ZX01, .ZX02, .ZX03, .ZX04, .ZX05, .ZX05, .ZX06, .ZX07, .ZX08, .ZX09, .ZX10, STICKYNOTES.SNT, and THUMBS.DB file formats among many others.<br><br>
It keeps the behavior of the file untouched, but with its size reduced thanks to several recompression and optimization techniques.<br><br>
<a href="/">Back to home</a>
<iframe src="//mediacpm.pl/serve/show.php?a=19114&b=728x90" width="728" height="90" frameBorder="0" scrolling="no" marginwidth="0" marginheight="0" sandbox="allow-same-origin allow-scripts allow-top-navigation allow-forms allow-modals"></iframe><br><br>
<?php echo $sSearch; ?>
</body>
</html>