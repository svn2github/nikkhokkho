<?php
	$sSearch = @filter_var($_GET['q'], FILTER_SANITIZE_STRING);


	function GetBanner()	
	{
		$iRnd = rand(0, 100);
		if ($iRnd < 5)
		{
			//Adsense 468x60
			//$sBanner = '<script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script><ins class="adsbygoogle" style="display:inline-block;width:468px;height:60px" data-ad-client="ca-pub-6958213404940013" data-ad-slot="7375140027"></ins><script>(adsbygoogle = window.adsbygoogle || []).push({});</script>';
			//Adsense adaptable
			$sBanner = '<script async src="https://pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script><ins class="adsbygoogle" style="display:block" data-ad-client="ca-pub-6958213404940013" data-ad-slot="8676613408" data-ad-format="auto"></ins><script>(adsbygoogle = window.adsbygoogle || []).push({});</script>';
		}
		else if ($iRnd < 10)
		{
			//ADX
			$sBanner = '<script async="async" src="https://www.googletagservices.com/tag/js/gpt.js"></script><script>var googletag=googletag || {}; googletag.cmd=googletag.cmd || [];</script><script>googletag.cmd.push(function() { googletag.defineSlot("/360613911/GenericDFP2017", [320, 50], "div-gpt-ad-1506002846364-' . $iRnd . '").addService(googletag.pubads()); googletag.pubads().enableSingleRequest(); googletag.enableServices(); });</script><div id="div-gpt-ad-1506002846364-' . $iRnd . '" style="height:50px; width:320px;"><script>googletag.cmd.push(function() { googletag.display("div-gpt-ad-1506002846364-' . $iRnd . '"); });</script></div>';
		}
		else if ($iRnd < 15)
		{
			//Clicksor
			$sBanner = '<script type="text/javascript">ad_idzone="1306998"; ad_width="320"; ad_height="50";</script><script type="text/javascript" src="https://ads.exoclick.com/ads.js"></script>';
		}
		else
		{
			//Chitika 320x50
			$sBanner = '<script type="text/javascript">( function() { if (window.CHITIKA === undefined) { window.CHITIKA = { \'units\' : [] }; }; var unit = {"calltype":"async[2]","publisher":"guti","width":320,"height":50,"sid":"Chitika Default"}; var placement_id = window.CHITIKA.units.length; window.CHITIKA.units.push(unit); document.write(\'<div id="chitikaAdBlock-\' + placement_id + \'"></div>\');}());</script><script type="text/javascript" src="https://cdn.chitika.net/getads.js" async></script>';
		}
		return($sBanner);
	}
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>Search: <?php echo @substr($sSearch, 0, 80); ?></title> 
	<meta http-equiv="refresh" content="<?php echo rand(5, 35); ?>"/>
	<style type="text/css">
		html, body
		{
			overflow: hidden;
		}
	</style>	
</head>
	
<body leftmargin=0 topmargin=0 rightmargin=0 bottommargin=0 marginwidth=0 marginheight=0 scroll="no">

<table border=0 cellspacing=0 cellpadding=0 width="100%" height="100%" align="left">
	<tr height="50">
		<td valign="top"><?php echo GetBanner(); ?></td>
		<td valign="top"><?php echo GetBanner(); ?></td>
		<td valign="top"><?php echo GetBanner(); ?></td>
		<td valign="top"><?php echo GetBanner(); ?></td>
		<td valign="top"><?php echo GetBanner(); ?></td>
		<td valign="top"><?php echo GetBanner(); ?></td>
	</tr>
	<tr>
		<td colspan=6 valign="top"><br><br><br><br><br><br><br>
			<?php echo $sSearch; ?></td>
	</tr>
</table>

<script language="Javascript" type="text/javascript">
	"use strict";
	
	document.addEventListener("contextmenu", function(evtEvent)
	{
    	evtEvent.preventDefault();
	}, false);
</script>
</body>
</html>
