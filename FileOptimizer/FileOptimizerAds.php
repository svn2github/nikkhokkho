<?php
	$iWidth = @filter_var($_GET['w'], FILTER_SANITIZE_NUMBER_INT);
	if ($iWidth == 0)
	{
		$iWidth = 640;
	}
	$iHeight = @filter_var($_GET['h'], FILTER_SANITIZE_NUMBER_INT);
	if ($iHeight == 0)
	{
		$iHeight = 50;
	}
	$iDebug = @filter_var($_GET['d'], FILTER_SANITIZE_NUMBER_INT);
	$sSearch = @filter_var($_GET['q'], FILTER_SANITIZE_STRING);

	function GetBanner()	
	{
		global $iWidth, $iHeight;
		static $iCont = 0;
		$iRnd = mt_rand(0, 100);
		$iCont++;

		if ($iRnd < 1)
		{
			if ($iHeight >= 90)
			{
				//Adsense 728x90
				$sBanner = '<script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script><ins class="adsbygoogle" style="display:inline-block;width:728px;height:90px" data-ad-client="ca-pub-6958213404940013" data-ad-slot="6985177659"></ins><script>(adsbygoogle = window.adsbygoogle || []).push({});</script>';
			}
			else
			{
				//Adsense adaptable
				$sBanner = '<script async src="https://pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script><ins class="adsbygoogle" style="display:block" data-ad-client="ca-pub-6958213404940013" data-ad-slot="8676613408" data-ad-format="auto"></ins><script>(adsbygoogle = window.adsbygoogle || []).push({});</script>';
			}
		}
		else if ($iRnd < 2)
		{
			if ($iHeight >= 90)
			{
				//ADX
				$sBanner = '<script async="async" src="https://www.googletagservices.com/tag/js/gpt.js"></script><script>var googletag=googletag || {}; googletag.cmd=googletag.cmd || [];</script><script>googletag.cmd.push(function() { googletag.defineSlot("/360613911/GenericDFP2017", [728, 90], "div-gpt-ad-1506002846364-' . $iCont . '").addService(googletag.pubads()); googletag.pubads().enableSingleRequest(); googletag.enableServices(); });</script><div id="div-gpt-ad-1506002846364-' . $iCont . '" style="height:90px; width:728px;"><script>googletag.cmd.push(function() { googletag.display("div-gpt-ad-1506002846364-' . $iCont . '"); });</script></div>';
			}
			else
			{			
				//ADX
				$sBanner = '<script async="async" src="https://www.googletagservices.com/tag/js/gpt.js"></script><script>var googletag=googletag || {}; googletag.cmd=googletag.cmd || [];</script><script>googletag.cmd.push(function() { googletag.defineSlot("/360613911/GenericDFP2017", [320, 50], "div-gpt-ad-1506001695132-' . $iCont . '").addService(googletag.pubads()); googletag.pubads().enableSingleRequest(); googletag.enableServices(); });</script><div id="div-gpt-ad-1506001695132-' . $iCont . '" style="height:50px; width:320px;"><script>googletag.cmd.push(function() { googletag.display("div-gpt-ad-1506001695132-' . $iCont . '"); });</script></div>';
			}
		}
		else if ($iRnd < 5)
		{
			if ($iHeight >= 15)
			{
				//Clicksor
				$sBanner = '<script type="text/javascript">ad_idzone="1306998"; ad_width="728"; ad_height="90";</script><script type="text/javascript" src="https://ads.exoclick.com/ads.js"></script>';
			}
			else
			{
				//Clicksor
				$sBanner = '<script type="text/javascript">ad_idzone="1306998"; ad_width="320"; ad_height="50";</script><script type="text/javascript" src="https://ads.exoclick.com/ads.js"></script>';
			}
		}
		else
		{
			if ($iHeight >= 90)
			{
				//Chitika 728x90
				$sBanner = '<script type="text/javascript">( function() { if (window.CHITIKA === undefined) { window.CHITIKA = { \'units\' : [] }; }; var unit = {"calltype":"async[2]","publisher":"guti","width":728,"height":90,"sid":"Chitika Default"}; var placement_id = window.CHITIKA.units.length; window.CHITIKA.units.push(unit); document.write(\'<div id="chitikaAdBlock-\' + placement_id + \'"></div>\');}());</script><script type="text/javascript" src="https://cdn.chitika.net/getads.js" async></script>';
			}
			else
			{
				//Chitika 320x50
				$sBanner = '<script type="text/javascript">( function() { if (window.CHITIKA === undefined) { window.CHITIKA = { \'units\' : [] }; }; var unit = {"calltype":"async[2]","publisher":"guti","width":320,"height":50,"sid":"Chitika Default"}; var placement_id = window.CHITIKA.units.length; window.CHITIKA.units.push(unit); document.write(\'<div id="chitikaAdBlock-\' + placement_id + \'"></div>\');}());</script><script type="text/javascript" src="https://cdn.chitika.net/getads.js" async></script>';
			}
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
	?>
	<style type="text/css">
		html, body
		{
			overflow: hidden;
		}
	</style>
	<base target="_blank"/>
</head>
	
<body leftmargin=0 topmargin=0 rightmargin=0 bottommargin=0 marginwidth=0 marginheight=0 scroll="no">

<table border=0 cellspacing=0 cellpadding=0 width="100%">
	<?php
		if ($iHeight >= 90)
		{
			$iBanners = ceil($iWidth / 728);
		}
		else
		{
			$iBanners = ceil($iWidth / 320);
		}
	?>
	<tr height="<?php echo $iHeight; ?>">
		<?php
			for ($iBanner = 0; $iBanner < $iBanners; $iBanner++)
			{
		?>
				<td valign="top"><?php echo GetBanner(); ?></td>
		<?php
			}
		?>
	</tr>
	<tr>
		<td colspan=<?php echo $iBanners; ?> valign="top"><br><br><br><br><br><br><br>
			<?php echo $sSearch; ?></td>
	</tr>
</table>
			
			
<script language="Javascript" type="text/javascript">
	"use strict";

	document.addEventListener('click', function(poEvent)
	{
	    var oTarget = poEvent.target;
	    do
	    {
	        if ((oTarget.nodeName.toUpperCase() === 'A') && (oTarget.href))
	        {
	            oTarget.target = '_blank';
	            break;
	        }
	    }
	    while (oTarget = oTarget.parentElement);
	}, true);


	<?php
		if ($iDebug !== 1)
		{
	?>
			document.addEventListener('contextmenu', function(poEvent)
			{
		    	poEvent.preventDefault();
			}, false);
	<?php
		}
	?>
</script>


</body>
</html>