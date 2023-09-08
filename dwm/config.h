/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "chromium"
/* systray */
static const int showsystray        = 1;        /* 0 means no systray */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
/* appearance */
static unsigned int borderpx  = 0;              /* border pixel of windows */
static unsigned int snap      = 32;             /* snap pixel */
static unsigned int gappih    = 5;             /* horiz inner gap between windows */
static unsigned int gappiv    = 5;             /* vert inner gap between windows */
static unsigned int gappoh    = 5;             /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 5;             /* vert outer gap between windows and screen edge */
static int swallowfloating    = 0;              /* 1 means swallow floating windows by default */
static int smartgaps          = 0;              /* 1 means no outer gap when there is only one window */
static int showbar            = 1;              /* 0 means no bar */
static int topbar             = 1;              /* 0 means bottom bar */
static char *fonts[]          = {"Liberation Mono:pixelsize=10","WenQuanYi Micro Hei Mono:size=10","SauceCodePro Nerd Font Mono:size=14"};
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#222222";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#222222";
static char selbgcolor[]            = "#222222";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spcalc",      spcmd2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class    instance           title       	 tags mask    isfloating   isterminal  noswallow  monitor */
	{ "Gimp",     NULL,            NULL,       	    1 << 8,       0,           0,         0,        -1 },
	{ TERMCLASS,  NULL,            NULL,       	    0,            0,           1,         0,        -1 },
	{ NULL,       NULL,            "Event Tester",  0,            0,           0,         1,        -1 },
	{ TERMCLASS,  "floatterm",     NULL,       	    0,            1,           1,         0,        -1 },
	{ TERMCLASS,  "bg",            NULL,       	    1 << 7,       0,           1,         0,        -1 },
	{ TERMCLASS,  "spterm",        NULL,       	    SPTAG(0),     1,           1,         0,        -1 },
	{ TERMCLASS,  "spcalc",        NULL,       	    SPTAG(1),     1,           1,         0,        -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",	tile },			/* Default: Master on left, slaves on right */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_h,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_l,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };


#include <X11/XF86keysym.h>
#include "shiftview.c"
static const char *upvol[]   = { "/home/Spike/scripts/vol-up.sh",  NULL };
static const char *downvol[] = { "/home/Spike/scripts/vol-down.sh",  NULL };
static const char *mutevol[] = { "/home/Spike/scripts/vol-toggle.sh",  NULL };
static const Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	TAGKEYS(XK_1,0)
	TAGKEYS(XK_2,1)
	TAGKEYS(XK_3,2)
	TAGKEYS(XK_4,3)
	TAGKEYS(XK_5,4)
	TAGKEYS(XK_6,5)
	TAGKEYS(XK_7,6)
	TAGKEYS(XK_8,7)
	TAGKEYS(XK_9,8)
	{ MODKEY, XK_0,view,{.ui = ~0 } },
	/* { MODKEY|ShiftMask,XK_0,tag,{.ui = ~0 } }, */
	{ MODKEY,XK_Tab,view,{0} },
	{ MODKEY,XK_grave,shiftview,	{ .i = +1 } },
	{ MODKEY,XK_q,killclient,	{0} },
  { MODKEY|ControlMask,XK_Delete,quit,{0} },


	{ MODKEY,XK_c,spawn,{.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY,XK_a,togglegaps,	{0} },
	{ MODKEY,XK_d,spawn,{.v = (const char*[]){ "dmenu_run", NULL } } },
	{ MODKEY,XK_f,togglefullscr,{0} },
	{ MODKEY,XK_Return,	spawn,{.v = termcmd } },
	{ MODKEY,XK_b,togglebar,{0} },
	/* { MODKEY,XK_N,spawn,SHCMD(TERMINAL " -e newsboat ") }, */


	{ 0,XK_F1,spawn,{.v = mutevol }},
	{ 0,XK_F2,spawn,{.v = downvol }},
	{ 0,XK_F3,spawn,{.v = upvol   }},
	{ 0,XK_F11,spawn,SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },


	{ MODKEY,XK_Left,setmfact, {.f = -0.05} },
	{ MODKEY,XK_Right,setmfact,{.f = +0.05} },
	{ MODKEY,XK_BackSpace,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
	{ MODKEY,XK_space,	zoom,		{0} },
	{ MODKEY|ShiftMask,		XK_space,	togglefloating,	{0} },
	{ MODKEY,XK_Scroll_Lock,	spawn,		SHCMD("killall screenkey || screenkey &") },

	{ 0,     XK_Print,	spawn,		SHCMD( "maim -s | tee ~/Pictures/$(date +%s).png | xclip -selection clipboard -t image/png") },


};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	/* { ClkStatusText,        0,              Button1,        spawn,          SHCMD(TERMINAL     " -e alsamixer") }, */
	{ ClkClientWin,         ControlMask,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         ControlMask,         Button3,        resizemouse,    {0} },
	/* { ClkClientWin,          MODKEY,         Button2,        defaultgaps,    {0} }, */
	/* { ClkClientWin,      		MODKEY,		      Button4,	      incrgaps,	{.i = +1} }, */
	/* { ClkClientWin,      		MODKEY,		      Button5,	      incrgaps,	{.i = -1} }, */
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	/* { ClkTagBar,            0,              Button3,        toggleview,     {0} }, */
	/* { ClkTagBar,            MODKEY,         Button1,        tag,            {0} }, */
	/* { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} }, */
	/* { ClkTagBar,		        0,		          Button4,	      shiftview,{.i = -1} }, */
	/* { ClkTagBar,		        0,		          Button5,	      shiftview, {.i = 1} }, */
	/* { ClkRootWin,		      0,		          Button2,	      togglebar,      {0} }, */
};

/* Xresources preferences to load at startup */
ResourcePref resources[] = {
		{ "color0",		STRING,	&normbordercolor },
		{ "color8",		STRING,	&selbordercolor },
		{ "color0",		STRING,	&normbgcolor },
		{ "color4",		STRING,	&normfgcolor },
		{ "color0",		STRING,	&selfgcolor },
		{ "color4",		STRING,	&selbgcolor },
		{ "borderpx",		INTEGER, &borderpx },
		{ "snap",		INTEGER, &snap },
		{ "showbar",		INTEGER, &showbar },
		{ "topbar",		INTEGER, &topbar },
		{ "nmaster",		INTEGER, &nmaster },
		{ "resizehints",	INTEGER, &resizehints },
		{ "mfact",		FLOAT,	&mfact },
		{ "gappih",		INTEGER, &gappih },
		{ "gappiv",		INTEGER, &gappiv },
		{ "gappoh",		INTEGER, &gappoh },
		{ "gappov",		INTEGER, &gappov },
		{ "swallowfloating",	INTEGER, &swallowfloating },
		{ "smartgaps",		INTEGER, &smartgaps },
};
