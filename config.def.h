/* appearance */

static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=15", "SymbolNerdFontMono-Regular:pixelsize=19" };
static const char dmenufont[]       = "monospace:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#9b99e8";
static const char *colors[][3]      = {

	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },

};

/* tagging */
static const char *tags[] = { "󰈹", "", "", "", "5", "6", "7", "", "󰓇" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */

	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },

};

/* layout(s) */

static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]",      tile },    
	{ "><>",      NULL },    
	{ "[M]",      monocle },
};

#define ALT Mod1Mask
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define SHCMD(cmd) { .v = (const char*[]){ cmd, NULL } }


static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char  *flameshot[] = { "flameshot", "gui",  NULL };
static const char *bri_increase[] = { "brightnessctl", "set", "1%+", NULL };
static const char *bri_decrease[] = { "brightnessctl", "set", "1%-", NULL };
static const char *shutdown[] = { "shutdown", "now", NULL };
static const char *termcmd[] = { "alacritty", NULL }; 

static const Key keys[] = {
	
	// Custom Keybindings
	{ ALT, 													XK_n, 		 spawn, 				 SHCMD ("obsidian" ) },
	{ ALT, 													XK_t, 		 spawn, 				 SHCMD ("thunar") },
	{ MODKEY,             					XK_Return, spawn,          { .v = termcmd } },
	{ MODKEY,  											XK_x,			 spawn, 				 SHCMD ("i3lock-fancy") },
	{ MODKEY, 											XK_b, 		 spawn, 				 SHCMD ("brave") },
	{ MODKEY, 											XK_d, 		 spawn, 				 SHCMD ("discord" ) },
	{ MODKEY, 											XK_s, 		 spawn, 				 SHCMD ("spotify" ) },
	{ MODKEY|ShiftMask,         		XK_p,      spawn,          SHCMD ("pavucontrol") },
	{ MODKEY|ALT|ShiftMask, 				XK_r, 		 spawn, 				 SHCMD ("reboot" ) },
	{ MODKEY|ShiftMask,         		XK_u,      spawn,          { .v = flameshot } },
	{ MODKEY,                       XK_r,      spawn,          { .v = dmenucmd } },
	{ MODKEY|ALT, 									XK_o, 		 spawn, 				 { .v = bri_decrease } },
	{ MODKEY|ALT, 									XK_i, 		 spawn, 				 { .v = bri_increase } },
	{ MODKEY|ALT|ShiftMask, 				XK_s, 		 spawn, 				 { .v = shutdown } },
	
	// Core functionality Keybindings
	{ MODKEY,             					XK_space,  setlayout,      {0} },
	{ MODKEY,             					XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,             					XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,             					XK_k,      focusstack,     {.i = +1 } },	
	{ MODKEY,             					XK_j,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY,             					XK_w,      killclient,     {0} },
	{ MODKEY,             					XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_z, 		 zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
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
	{ MODKEY|ShiftMask,             XK_c,      quit,           {0} },
};

/* button definitions */
static const Button buttons[] = {

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

