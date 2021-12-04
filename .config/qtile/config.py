#IMPORT
from typing import List  # noqa: F401
from libqtile import bar, layout, widget, hook
from libqtile.config import Click, Drag, Group, Key, Match, Screen
from libqtile.lazy import lazy
from libqtile.utils import guess_terminal
import os
import subprocess
import psutil

#autostart
@hook.subscribe.startup_once
def autostart():
    home = os.path.expanduser('~')
    subprocess.Popen([home + '/.config/qtile/autostart.sh'])

home = os.path.expanduser('~')

mod = "mod4"
terminal = "st"

keys = [
    # Switch between windows
    Key([mod], "h", lazy.layout.left(), desc="Move focus to left"),
    Key([mod], "l", lazy.layout.right(), desc="Move focus to right"),
    Key([mod], "j", lazy.layout.down(), desc="Move focus down"),
    Key([mod], "k", lazy.layout.up(), desc="Move focus up"),
    Key([mod], "space", lazy.layout.next(),
        desc="Move window focus to other window"),

    # Move windows between left/right columns or move up/down in current stack.
    # Moving out of range in Columns layout will create new column.
    Key([mod, "shift"], "h", lazy.layout.shuffle_left(),
        desc="Move window to the left"),
    Key([mod, "shift"], "l", lazy.layout.shuffle_right(),
        desc="Move window to the right"),
    Key([mod, "shift"], "j", lazy.layout.shuffle_down(),
        desc="Move window down"),
    Key([mod, "shift"], "k", lazy.layout.shuffle_up(), desc="Move window up"),

    # Grow windows. If current window is on the edge of screen and direction
    # will be to screen edge - window would shrink.
    Key([mod, "control"], "h", lazy.layout.grow_left(),
        desc="Grow window to the left"),
    Key([mod, "control"], "l", lazy.layout.grow_right(),
        desc="Grow window to the right"),
    Key([mod, "control"], "j", lazy.layout.grow_down(),
        desc="Grow window down"),
    Key([mod, "control"], "k", lazy.layout.grow_up(), desc="Grow window up"),
    Key([mod], "n", lazy.layout.normalize(), desc="Reset all window sizes"),

    # Toggle between split and unsplit sides of stack.
    # Split = all windows displayed
    # Unsplit = 1 window displayed, like Max layout, but still with
    # multiple stack panes
    Key([mod, "shift"], "Return", lazy.layout.toggle_split(),
        desc="Toggle between split and unsplit sides of stack"),
    Key([mod], "Return", lazy.spawn(terminal), desc="Launch terminal"),

    # Toggle between different layouts as defined below
    Key([mod], "Tab", lazy.next_layout(), desc="Toggle between layouts"),
    Key([mod, "shift"], "c", lazy.window.kill(), desc="Kill focused window"),

    Key([mod, "shift"], "r", lazy.restart(), desc="Restart Qtile"),
    Key([mod, "shift"], "q", lazy.shutdown(), desc="Shutdown Qtile"), 

    #next prev group
    Key([mod], "Right", lazy.screen.next_group(), desc="to the next group"),
    Key([mod], "Left", lazy.screen.prev_group(), desc="to the previous group"),

    #rofi
    Key([mod], "p", lazy.spawn(home + "/.config/qtile/scripts/rofi.sh"), desc="Spawn rofi"),
    Key([mod], "s", lazy.spawn("/home/eri/.config/qtile/scripts/powermenu.sh"), desc="Spawn powermenu"),
]

groups = [
        Group("1",
            label="",
            layout="monadtall"),

        Group("2",
            label="",
            layout="monadtall",
            matches=[Match(wm_class=["firefox"])]),

        Group("3",
            label="",
            layout="monadtall",
            matches=[Match(wm_class=["Spotify"])]),
        Group("4",
            label="",
            layout="monadtall",
            matches=[Match(wm_class=["Org.gnome.Nautilus"])]),
        Group("5",
            label="嗢",
            layout="monadtall",
            matches=[Match(wm_class=["vlc"])]),
        Group("6",
            label="﬏",
            layout="monadtall",
            matches=[Match(wm_class=["Code"])]),
        ]

for i in groups:
    keys.extend([
        # mod1 + letter of group = switch to group
        Key([mod], i.name, lazy.group[i.name].toscreen(),
            desc="Switch to group {}".format(i.name)),

        # mod1 + shift + letter of group = switch to & move focused window to group
        Key([mod, "shift"], i.name, lazy.window.togroup(i.name, switch_group=True),
            desc="Switch to & move focused window to group {}".format(i.name)),
        # Or, use below if you prefer not to switch to that group.
        # # mod1 + shift + letter of group = move focused window to group
        # Key([mod, "shift"], i.name, lazy.window.togroup(i.name),
        #     desc="move focused window to group {}".format(i.name)),
    ])

#colors
colors = []
cache=home + '/.cache/wal/colors'
def load_colors(cache):
    with open(cache, 'r') as file:
        for i in range(16):
            colors.append(file.readline().strip())
    colors.append('#ffffff')
    lazy.reload()
load_colors(cache)

#LAYOUT
layout_theme = {"border_width": 2,
                "margin": 8,
                "border_focus": colors[14],
                "border_normal": colors[0]}

layouts = [
    layout.MonadTall(**layout_theme),
    layout.Tile(**layout_theme),
    layout.Max(**layout_theme),
    layout.Floating(**layout_theme),
]

widget_defaults = dict(
    font='JetBrains Mono Bold',
    fontsize=12,
    padding=2,
)
extension_defaults = widget_defaults.copy()

sep1 = ""
sep2 = ""

screens = [
    Screen(
        top=bar.Bar(
            [
                widget.CurrentLayout(
                    background = colors[7],
                    foreground = colors[0],
                    padding = 4),
                widget.TextBox(
                    text = sep1,
                    font = "MesloLGS NF",
                    fontsize = 18,
                    foreground = colors[0],
                    background = colors[7],
                    padding = 0),
                widget.GroupBox(
                    font = "MesloLGS NF",
                    fontsize = 18,
                    borderwidth = 3,
                    rounded = False,
                    highlight_method = "line",
                    padding = 5,
                    spacing = 0,
                    urgent_alert_method = "line",
                    active = colors[6],
                    inactive = colors[7],
                    highlight_color = colors[0],
                    this_current_screen_border = colors[4],
                    urgent_border = colors[1],
                    urgent_text = colors[1],
                    background = colors[0]),
                widget.TextBox(
                    text = sep1,
                    font = "MesloLGS NF",
                    fontsize = 18,
                    foreground = colors[7],
                    background = colors[4],
                    padding = 0), 
                widget.Spacer(),
                widget.TextBox(
                    text = sep2,
                    font = "MesloLGS NF",
                    fontsize = 18,
                    foreground = colors[8],
                    background = colors[0],
                    padding = 0),
                widget.TextBox(
                    text = "",
                    background = colors[8],
                    foreground = colors[0],
                    font = "MesloLGS NF",
                    fontsize = 18,
                    padding = 4),
                widget.Volume(
                    background = colors[8],
                    foreground = colors[0],
                    padding = 5),
                widget.TextBox(
                    text = sep2,
                    font = "MesloLGS NF",
                    fontsize = 18,
                    foreground = colors[1],
                    background = colors[8],
                    padding = 0),
                widget.TextBox(
                    text = "",
                    background = colors[1],
                    foreground = colors[0],
                    font = "MesloLGS NF",
                    fontsize = 18,
                    padding = 4),
                widget.CheckUpdates(
                    display_format = "{updates}",
                    distro = "Arch",
                    update_interval = 60,
                    custom_command = "checkupdates ",
                    no_update_string = "None",
                    background = colors[1],
                    foreground = colors[0],
                    colour_no_updates = colors[0],
                    colour_have_updates = colors[0]),
                widget.TextBox(
                    text = sep2,
                    font = "MesloLGS NF",
                    fontsize = 18,
                    foreground = colors[2],
                    background = colors[1],
                    padding = 0),
                widget.Net(
                    interface = "tap-easytether",
                    format = "{down} ↓↑ {up} ",
                    update_interval = 1,
                    background = colors[2],
                    foreground = colors[0]),
                widget.TextBox(
                    text = sep2,
                    font = "MesloLGS NF",
                    fontsize = 18,
                    foreground = colors[3],
                    background = colors[2],
                    padding = 0),
                widget.TextBox(
                    text = "",
                    background = colors[3],
                    foreground = colors[0],
                    font = "MesloLGS NF",
                    fontsize = 18,
                    padding = 4),
                widget.DF(
                    format = "{uf} {m}iB ",
                    partition = "/",
                    visible_on_warn = False,
                    warn_space = 2,
                    foreground = colors[0],
                    background = colors[3],
                    warn_color = colors[1]),
                widget.TextBox(
                    text = sep2,
                    font = "MesloLGS NF",
                    fontsize = 18,
                    foreground = colors[4],
                    background = colors[3],
                    padding = 0),
                widget.TextBox(
                    text = "﬙",
                    background = colors[4],
                    foreground = colors[0],
                    font = "MesloLGS NF",
                    fontsize = 18,
                    padding = 4),
                widget.Memory(
                    format = "{MemUsed:.0f} {mm}iB ",
                    update_interval = 1.0,
                    measure_mem = "M",
                    background = colors[4],
                    foreground = colors[0]),
                widget.TextBox(
                    text = sep2,
                    font = "MesloLGS NF",
                    fontsize = 18,
                    foreground = colors[5],
                    background = colors[4],
                    padding = 0),
                widget.TextBox(
                    text = "",
                    background = colors[5],
                    foreground = colors[0],
                    font = "MesloLGS NF",
                    fontsize = 18,
                    padding = 4),
                widget.CPU(
                    format = "{load_percent}% ",
                    update_interval = 1.0,
                    background = colors[5],
                    foreground = colors[0]),
                widget.TextBox(
                    text = sep2,
                    font = "MesloLGS NF",
                    fontsize = 18,
                    foreground = colors[6],
                    background = colors[5],
                    padding = 0),
                widget.TextBox(
                    text = "",
                    background = colors[6],
                    foreground = colors[0],
                    fontsize = 20,
                    padding = 4,
                    font = "MesloLGS NF"),
                widget.Clock(
                    format = '%A %d - %H:%M',
                    background = colors[6],
                    foreground = colors[0],
                    padding = 4,
                    update_insterval = 1.0),
                widget.Systray(
                    background = colors[8],
                    icon_size = 20),
            ],
            22,
            background=colors[0]
        ),
    ),
]

# Drag floating layouts.
mouse = [
    Drag([mod], "Button1", lazy.window.set_position_floating(),
         start=lazy.window.get_position()),
    Drag([mod], "Button3", lazy.window.set_size_floating(),
         start=lazy.window.get_size()),
    Click([mod], "Button2", lazy.window.bring_to_front())
]

dgroups_key_binder = None
dgroups_app_rules = []  # type: List
follow_mouse_focus = True
bring_front_click = False
cursor_warp = False
floating_layout = layout.Floating(float_rules=[
    # Run the utility of `xprop` to see the wm class and name of an X client.
    *layout.Floating.default_float_rules,
    Match(wm_class='confirmreset'),  # gitk
    Match(wm_class='makebranch'),  # gitk
    Match(wm_class='maketag'),  # gitk
    Match(wm_class='ssh-askpass'),  # ssh-askpass
    Match(wm_class='alacritty'),
    Match(title='branchdialog'),  # gitk
    Match(title='pinentry'),  # GPG key password entry
],   
    border_focus=colors[14],
    border_normal=colors[0]
    )
auto_fullscreen = True
focus_on_window_activation = "smart"
reconfigure_screens = True

# If things like steam games want to auto-minimize themselves when losing
# focus, should we respect this or not?
auto_minimize = True

# XXX: Gasp! We're lying here. In fact, nobody really uses or cares about this
# string besides java UI toolkits; you can see several discussions on the
# mailing lists, GitHub issues, and other WM documentation that suggest setting
# this string if your java app doesn't work correctly. We may as well just lie
# and say that we're a working one by default.
#
# We choose LG3D to maximize irony: it is a 3D non-reparenting WM written in
# java that happens to be on java's whitelist.
wmname = "LG3D"
