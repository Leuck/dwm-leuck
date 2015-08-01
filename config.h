/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[] = "-misc-fixed-medium-r-semicondensed-*-13-*-*-*-*-*-*";
static const char normbordercolor[] = "#252525";
static const char normbgcolor[]     = "#555555";
static const char normfgcolor[]     = "#cdcdcd";
static const char selbordercolor[]  = "#2096b4";
static const char selbgcolor[]      = "#1692b0";
static const char selfgcolor[]      = "#ffffff";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class          instance    title          tags mask        isfloating   monitor */
	{ "Gimp",         NULL,        NULL,          0,                True,        -1 },
	{ "Tilda",        NULL,        NULL,          0,                True,        -1 },
	{ "qjackctl",     NULL,        NULL,          0,                True,        -1 },
	{ "MPlayer",      NULL,        NULL,          0,                True,        -1 },
	{ "Lxappearance", NULL,        NULL,          0,                True,        -1 },
	{ "Firefox",      "Download",  NULL,          0,                True,        -1 },
	{ "Firefox",      NULL,  "Firefox Preferences",     0,          True,        -1 },
	{ "Skype",        NULL,        NULL,          0,                True,        -1 },
	{ NULL,           NULL,        "Event Tester",        0,        True,        -1 },
	{ NULL,           NULL,        "Save File",           0,        True,        -1 },
	{ NULL,           NULL,        "File Operation Progress",   0,  True,        -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;     /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in 
tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[t]",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[ ]",      monocle },
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
static const char *dmenucmd[]	= { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]	= { "urxvt", NULL };
static const char *volup[]	= { "amixer", "set", "Master,0", "5%+,5%+", "unmute", NULL };
static const char *voldown[]	= { "amixer", "set", "Master,0", "5%-,5%-", "unmute", NULL };
static const char *browsercmd[]	= { "chromium", NULL };
static const char *filemgr[]	= { "dolphin", NULL };
static const char *mnext[]	= { "mpc", "next", "--host", "b3", NULL };
static const char *mprevious[]	= { "mpc", "prev", "--host", "b3", NULL };
static const char *mtoggle[]	= { "mpc", "toggle", "--host", "b3", NULL };
static const char *screenlock[] = { "i3lock", "--color=000000", NULL };
static const char *screenshot[]	= { "/home/leuck/documentos/scripts/autoscreenshot.sh", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,                             0xff61,   spawn,          {.v = screenshot } },
	{ 0,                         0x1008ff13,   spawn,          {.v = volup } },
	{ 0,                         0x1008ff11,   spawn,          {.v = voldown } },
	{ MODKEY,                       XK_i,      spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_o,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_u,      spawn,          {.v = filemgr } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = screenlock } },
	{ MODKEY,                       0xff53,    spawn,          {.v = mnext } },
	{ MODKEY,                       0xff51,    spawn,          {.v = mprevious } },
	{ MODKEY,                       0xff54,    spawn,          {.v = mtoggle } },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_e,      incnmaster,      {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,      {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
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
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

