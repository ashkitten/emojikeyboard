from collections import OrderedDict
import json, os

with open(os.path.join(os.path.dirname(__file__), "emojilib/emojis.json")) as f:
    emojilib = json.load(f)

with open(os.path.join(os.path.dirname(__file__), "emoji-data/emoji.json")) as f:
    emojidata = json.load(f)

tone_modifiers = [
    "1f3fb",
    "1f3fc",
    "1f3fd",
    "1f3fe",
    "1f3ff"
]

def uniq(seq):
    seen = set()
    seen_add = seen.add
    return [x for x in seq if not (x in seen or seen_add(x))]

categories = [category for category in uniq([emoji["category"] for emoji in emojidata if emoji["category"] != "Skin Tones"])]

emoji_dict = {
    "categories": categories,
    "emojis": [],
    "categoryMap": {},
    "emojiMap": {},
}

for category in categories:
    emoji_dict["categoryMap"][category] = []

    for emoji in emojidata:
        if emoji["category"] == category and emoji["name"] is not None:
            if os.path.isfile(os.path.join(os.path.dirname(__file__), "twemoji/2/svg/{}.svg".format(emoji["unified"].lower()))):
                unicode = emoji["unified"].lower()
            elif os.path.isfile(os.path.join(os.path.dirname(__file__), "twemoji/2/svg/{}.svg".format(emoji["non_qualified"].lower()))):
                unicode = emoji["non_qualified"].lower()
            else:
                continue

            name = emoji["name"].title()
            characters = "".join([chr(int(codepoint, 16)) for codepoint in unicode.split("-")])
            has_tone_modifiers = any(m.lower() in unicode for m in tone_modifiers)
            is_tone_modifier = unicode.lower() in tone_modifiers

            try:
                keywords = ",".join([e["keywords"] for e in emojilib.values() if e["char"] == characters][0])
            except IndexError:
                keywords = ""

            data = {
                "name": name,
                "unicode": unicode,
                "characters": characters,
                "category": category,
                "hasToneModifiers": has_tone_modifiers,
                "isToneModifier": is_tone_modifier,
                "keywords": keywords,
            }

            emoji_dict["emojis"].append(unicode)
            emoji_dict["categoryMap"][category].append(data)
            emoji_dict["emojiMap"][unicode] = data

with open(os.path.join(os.path.dirname(__file__), "emoji.json"), "w") as f:
    json.dump(emoji_dict, f, indent=4)
