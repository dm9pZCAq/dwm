/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 3;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "terminus:size=10" };
static const char dmenufont[]       = "terminus:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char * const colors[][3] = {
	/*               fg           bg           border         */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};
static XrdbColor xrdb_colors[] = {
	{ "dwm.normbordercolor", normbordercolor },
	{ "dwm.normbgcolor",     normbgcolor },
	{ "dwm.normfgcolor",     normfgcolor },
	{ "dwm.selbordercolor",  selbordercolor },
	{ "dwm.selbgcolor",      selbgcolor },
	{ "dwm.selfgcolor",      selfgcolor },
};

/* autostart */
static const void *autostart[] = {
	&(const char *[]){ "clayout", NULL },
	&(const char *[]){ "aslstatus", NULL },
};

/* tagging */
static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class		instance	title	tags mask	isfloating	monitor */
	{ "qutebrowser",	NULL,		NULL,	1 << 2,		0,		-1 },
	{ "Chromium",		NULL,		NULL,	1 << 2,		0,		-1 },
	{ "IceCat",		NULL,		NULL,	1 << 2,		0,		-1 },
	{ "Telegram",		NULL,		NULL,	1 << 1,		0,		-1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "HHH",      grid },

	{ "[@]",      spiral },
	{ "[\\]",     dwindle },

	{ "[D]",      deck },
	{ "[M]",      monocle },

	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },

	{ "><>",      NULL },  /* no layout function means floating behavior */
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
#define INTERM(cmd) { .v = (const char*[]){ "st", "-e", cmd, NULL } }

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
	NULL
};
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_F1,     spawn,          SHCMD("qutebrowser") },
	{ MODKEY,                       XK_F2,     spawn,          SHCMD("telegram-desktop") },
	{ MODKEY,                       XK_F3,     spawn,          SHCMD("chromium") },
	{ MODKEY,                       XK_F4,     spawn,          SHCMD("icecat") },
	{ MODKEY,                       XK_F5,     spawn,          SHCMD("brightnessctl -q s 5%-") },
	{ MODKEY,                       XK_F6,     spawn,          SHCMD("brightnessctl -q s +5%") },
	{ MODKEY,                       XK_F9,     spawn,          SHCMD("mpc toggle") },
	{ MODKEY,                       XK_F10,    spawn,          SHCMD("pamixer -t") },
	{ MODKEY,                       XK_F11,    spawn,          SHCMD("pamixer -d 1") },
	{ MODKEY,                       XK_F12,    spawn,          SHCMD("pamixer -i 1") },

	{ MODKEY|ShiftMask,             XK_f,      spawn,          INTERM("/usr/local/bin/lf")},
	{ MODKEY|ShiftMask,             XK_m,      spawn,          INTERM("ncmpcpp")},
	{ MODKEY|ShiftMask,             XK_s,      spawn,          INTERM("stig")},
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("mpv -- $(xclip -o)")},
	{ MODKEY|Mod1Mask,              XK_r,      spawn,          SHCMD("record")},

	{ 0,                            XK_Print,  spawn,          SHCMD("maim -qui $(xdotool getactivewindow) | xclip -selection clipboard -t image/png") },
	{ ShiftMask,                    XK_Print,  spawn,          SHCMD("maim -qu | xclip -selection clipboard -t image/png") },
	{ ControlMask,                  XK_Print,  spawn,          SHCMD("maim -qus | xclip -selection clipboard -t image/png") },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[1]} }, /* bstack */
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[5]} }, /* monocle */
	{ MODKEY,                       XK_i,      setlayout,      {.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,             XK_i,      setlayout,      {.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[8]} }, /* floating */
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_F5,     xrdb,           {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD("$HOME/.config/dwm/exit") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

