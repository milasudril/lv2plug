#!/usr/bin/env php
<?php
function outputRedirect(string $filename)
	{
	global $ob_file;
	$ob_file=fopen($filename,'w');
	function ob_file_callback($buffer)
		{
		global $ob_file;
		fwrite($ob_file,$buffer);
		}
	ob_start('ob_file_callback');
	}

function CamelCase(string $str)
	{
//TODO: Use preg_split instead...
	$x=explode(' ',$str);
	foreach($x as &$namepart)
		{$namepart=ucfirst($namepart);}
	return implode('',$x);
	}

function guardname(string $scope,string $filename)
	{
//TODO: Use preg_split instead...
	$x=[$scope];
	$x=array_merge($x,explode('.',$filename));
	foreach($x as &$namepart)
		{$namepart=strtoupper($namepart);}
	return implode('_',$x);
	}

function cxxconstant(string $name)
	{
//TODO: Use preg_split instead...
	$x=explode(' ',$name);
	foreach($x as &$namepart)
		{$namepart=strtoupper($namepart);}
	return implode('_',$x);
	}

function typeGet($port)
	{
	$ret='';
	if($port->{'direction'}=='in')
		{$ret.='const ';}
	$typemap=array('MIDI'=>'LV2_Atom_Sequence'
		,'Audio'=>'float'
		,'Control'=>'float');
	$ret.=$typemap[$port->{'type'}].'*';
	return $ret;
	}

if($argc<2)
	{
	error_log('No input file is specified');
	exit(-1);
	}

if($argc<3)
	{
	error_log('No target header file is specified');
	exit(-1);
	}
outputRedirect($argv[2]);
$plugindata=json_decode(file_get_contents($argv[1]));
$name=$plugindata->{'name'};
$namespace=CamelCase($name);
$guard=guardname($namespace,$argv[2]);
?>
// This file has been generated by <?=$argv[0]?>

#ifndef <?=$guard?>

#define <?=$guard?>

#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/atom/util.h>

namespace <?=$namespace?>

	{
<?php foreach($plugindata as $field => $value)
	{
	if(!is_array($value))
		{?>
	constexpr const char* <?=cxxconstant($field)?>="<?=$value?>";
<?php	}
	}?>
	constexpr unsigned int PORT_COUNT=<?=count($plugindata->{'ports'}) ?>;

	namespace Ports
		{
<?php foreach($plugindata->{'ports'} as $index=>$port) {?>
		constexpr unsigned int <?=cxxconstant($port->{'name'})?>=<?=$index ?>;
<?php }?>

		template<unsigned int port_id>
		struct TypeGet
			{typedef void type;};

<?php foreach($plugindata->{'ports'} as $index=>$port) {?>
		template<>
		struct TypeGet<<?=cxxconstant($port->{'name'})?>>
			{typedef <?=typeGet($port)?> type;};

<?php }?>
		constexpr const char* PORTNAMES[]={<?php foreach($plugindata->{'ports'} as $index=>$port)
	{
	echo '"'.$port->{'name'}.'",';
	}?>nullptr};
		}

	class PortMap
		{
		public:
			template<unsigned int port_id>
			auto get() noexcept
				{
				static_assert(port_id < PORT_COUNT,"Bad port number");
				return reinterpret_cast<typename Ports::TypeGet<port_id>::type>(ports[port_id]);
				}

			PortMap& connect(unsigned int port_index,void* buffer) noexcept
				{
				ports[port_index]=buffer;
				return *this;
				}

		private:
			void* ports[PORT_COUNT];
		};
	};
#endif
