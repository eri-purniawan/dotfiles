/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 4;   /* systray spacing */
static unsigned int systrayiconsize = 20;
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static int barvertpad         	    = 6;        /* vertical padding for status text */
static const int user_bh            = 24;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = {// "Iosevka,Iosevka Medium:style=Medium,Regular:size=11",
					"JetBrains Mono:style=Bold:size=10",
					"MesloLGS NF:style=Bold:size=14",
					"PowerlineSymbols:style=Medium:size=20"};
static const char dmenufont[]       = "JetBrains Mono:style=Medium, Regular:size=10:antialias=true:autohinting=true";

static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char termcol0[] = "#000000"; /* black   */
static char termcol1[] = "#ff0000"; /* red     */
static char termcol2[] = "#33ff00"; /* green   */
static char termcol3[] = "#ff0099"; /* yellow  */
static char termcol4[] = "#0066ff"; /* blue    */
static char termcol5[] = "#cc00ff"; /* magenta */
static char termcol6[] = "#00ffff"; /* cyan    */
static char termcol7[] = "#d0d0d0"; /* white   */
static char termcol8[]  = "#808080"; /* black   */
static char termcol9[]  = "#ff0000"; /* red     */
static char termcol10[] = "#33ff00"; /* green   */
static char termcol11[] = "#ff0099"; /* yellow  */
static char termcol12[] = "#0066ff"; /* blue    */
static char termcol13[] = "#cc00ff"; /* magenta */
static char termcol14[] = "#00ffff"; /* cyan    */
static char termcol15[] = "#ffffff"; /* white   */
static char *termcolor[] = {
  termcol0,
  termcol1,
  termcol2,
  termcol3,
  termcol4,
  termcol5,
  termcol6,
  termcol7,
  termcol8,
  termcol9,
  termcol10,
  termcol11,
  termcol12,
  termcol13,
  termcol14,
  termcol15,
};
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selbgcolor,  termcol0,  selbordercolor  },
       [SchemeTitle]  = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeTray] = { normfgcolor, termcol0, termcol0 }, //systray background color
      /* [SchemeOcc] = { termcol3, normbgcolor, normbgcolor },*/
};

/* tagging */
static const char *tags[] = { "???", "???", "???", "???", "???", "???", "???"};

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title  tags mask  switchtotag    isfloating   isterminal	monitor */
	{ "firefox",  	NULL,   NULL,  	1 << 1,       	1,      0,      	0,	-1 },
	{ "Code",	NULL,	NULL,	1 << 2,		1,	0,		0,	-1 },
	{ "Pcmanfm",	NULL,	NULL,	1 << 3, 	1,	0,		0,	-1 },
	{ "Nitrogen",	NULL,	NULL,	0,		0,	1,		0,	-1 },
	{ "Lxappearance",NULL,	NULL,	0,		0,	1,		0,	-1 },
	{ "libreoffice-startcenter",NULL,NULL,1 << 4,	1,	0,		0,	-1 },
	{ "libreoffice-writer",NULL,NULL,1 << 4,	1,	0,		0,	-1 },
	{ "Mendeley Desktop",	NULL,NULL,1 << 4,	1,	0,		0,	-1 },
	{ "TelegramDesktop",NULL,NULL,	1 << 5,		1,	1,		0,	-1 },
	{ "St", 	NULL,	NULL,	0,		0,	0,		1,	-1 },
	{ "St", 	NULL,"ranger",	0,		0,	0,		1,	-1 },
	{ "discord",NULL,NULL,		1 << 6,		1,	0,		0,	-1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { 
	"dmenu_run", 
	"-m", dmenumon, 
	"-fn", dmenufont, 
	"-nb", normbgcolor, 
	"-nf", normfgcolor, 
	"-sb", selbgcolor, 
	"-sf", selfgcolor, 
	"-c",
	"-p", "Run",
	NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *rofi[] = { "/home/eri/suckless/dwm/scripts/rofi.sh", NULL };
static const char *powermenu[] = { "/home/eri/suckless/dwm/scripts/powermenu.sh", NULL };
static const char *lockscreen[] = { "betterlockscreen", "-l", "dimblur", NULL };
static const char *print_scrn[] = { "/home/eri/suckless/dwm/scripts/screenshot.sh", NULL };
static const char *mocp[] = { "st", "-e", "mocp", NULL };
//volume
static const char *upvol[]   = { "/home/eri/suckless/dwm/scripts/volume-button.sh", "4",     NULL };
static const char *downvol[] = { "/home/eri/suckless/dwm/scripts/volume-button.sh", "5",     NULL };
static const char *mutevol[] = { "/home/eri/suckless/dwm/scripts/volume-button.sh", "1",     NULL };

/* commands spawned when clicking statusbar, the mouse button pressed is exported as BUTTON */
static const StatusCmd statuscmds[] = {
	{ "/home/eri/suckless/dwm/scripts/resources.sh", 1 },
	{ "/home/eri/suckless/dwm/scripts/hdd-usage-button.sh", 2 },
	{ "/home/eri/suckless/dwm/scripts/rofi-cal.sh", 3 },
	{ "/home/eri/suckless/dwm/scripts/update-notifier", 4 },
	{ "/home/eri/suckless/dwm/scripts/netspeed-button.sh", 5 },
	{ "/home/eri/suckless/dwm/scripts/volume-button.sh", 6},
};
static const char *statuscmd[] = { "/bin/sh", "-c", NULL, NULL };

#include "nextprevtag.c"
#include "movestack.c"
#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = rofi } },
	{ MODKEY,		        XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|Mod1Mask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,    		XK_r,      quit,           {1} }, 
	//movestack
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	//nextprev
	{ MODKEY,              		XK_Right,           	view_adjacent,  { .i = +1 } },
	{ MODKEY,              		XK_Left,          	view_adjacent,  { .i = -1 } },
	//xrdb
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
	//powermenu
	{ MODKEY,			XK_s,		spawn,	{.v = powermenu} },
	{ MODKEY,			XK_x,		spawn,	{.v = lockscreen} },
	//scrot
	{ MODKEY,			XK_c,	spawn,	{.v = print_scrn} },
	//mocp
	{ MODKEY|ShiftMask,		XK_m,	spawn,		{.v = mocp} },
	//volume
	{ MODKEY,                       XK_F10, spawn, {.v = downvol } },
	{ MODKEY,                       XK_F9,  spawn, {.v = mutevol } },
	{ MODKEY,                       XK_F11, spawn, {.v = upvol   } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button4,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button5,        spawn,          {.v = statuscmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

