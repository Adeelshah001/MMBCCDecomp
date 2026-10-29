#!/usr/bin/env python3
"""Audio engine identification (signatures + structural hunt). Read-only."""
import re

ROM_PATH = "/home/hatch/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba"
rom = open(ROM_PATH, "rb").read()
N = len(rom)

def u32(o): return rom[o] | (rom[o+1] << 8) | (rom[o+2] << 16) | (rom[o+3] << 24)

# ---------- 1. keyword strings ----------
keywords = [b"Sappy", b"sappy", b"MPlay", b"MP2K", b"SoundDriver", b"SOUNDDRV",
            b"DirectSound", b"BGM_", b"bgm_", b"ME_", b"SE_", b"Song", b"song",
            b"Midi", b"MIDI", b"SMF", b"Capcom", b"CAPCOM", b"AIF", b"Sample",
            b"Wave", b"WAVE", b"PCM", b"MusicPlayer", b"m4a", b"M4A",
            b"jingle", b"fanfare", b"Voice", b"VOICE"]
print("== keyword hits ==", flush=True)
for kw in keywords:
    offs = [m.start() for m in re.finditer(re.escape(kw), rom)]
    if offs:
        ctx = []
        for o in offs[:5]:
            s = o
            while s > 0 and 32 <= rom[s-1] < 127 and s > o - 40: s -= 1
            e = o + len(kw)
            while e < N and 32 <= rom[e] < 127 and e < o + 60: e += 1
            ctx.append(rom[s:e][:70])
        print(f"  {kw.decode()}: {len(offs)} hits e.g.", flush=True)
        for c in ctx[:3]:
            try: print(f"    0x? {c.decode()}", flush=True)
            except: pass

# ---------- 2. printable-string dump: grep for audio-ish words ----------
strs = re.compile(rb'[A-Za-z][A-Za-z0-9_ ]{3,40}')
audio_words = ("bgm", "se_", "me_", "song", "music", "sound", "wave", "pcm",
               "midi", "jingle", "voice", "drum", "inst")
found = {}
for m in strs.finditer(rom):
    s = m.group().decode("ascii", "replace")
    low = s.lower()
    for w in audio_words:
        if w in low:
            found.setdefault(w, []).append((m.start(), s))
print("\n== audio-ish strings ==", flush=True)
for w, lst in found.items():
    print(f"  '{w}': {len(lst)}", flush=True)
    for o, s in lst[:8]:
        print(f"    0x{o:07X}: {s}", flush=True)

# ---------- 3. song-table hunt: runs of pointers -> headers w/ track-count shape ----------
# M4A SongHeader: u8 nTracks(1..16), u8 nBlocks, u8 prio, u8 reverb, u32 tone ptr, ...
print("\n== song-table-like pointer runs ==", flush=True)
o = 0
cands = []
while o < N - 4:
    v = u32(o)
    if 0x08000000 <= v < 0x08800000:
        run = [v]; p = o + 4
        while p < N - 4:
            v2 = u32(p)
            if not (0x08000000 <= v2 < 0x08800000): break
            if v2 <= run[-1]: break
            run.append(v2); p += 4
        if len(run) >= 4:
            # check targets: first byte 1..24 (track count), next bytes small
            ok = 0
            for t in run[:8]:
                to = t - 0x08000000
                if to + 8 <= N and 1 <= rom[to] <= 24 and rom[to+1] <= 24 and rom[to+2] <= 8:
                    ok += 1
            if ok >= 3:
                cands.append((o, len(run), ok))
        o = p if len(run) >= 4 else o + 4
        continue
    o += 4
print(f"  pointer runs whose targets look like song headers: {len(cands)}", flush=True)
for o, n, ok in cands[:20]:
    print(f"  table@0x{o:07X} nptrs={n} headerlike={ok}", flush=True)
print("DONE", flush=True)
