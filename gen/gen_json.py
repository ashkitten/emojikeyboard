from collections import OrderedDict
import json, os, itertools

with open(os.path.join(os.path.dirname(__file__), "emoji-data/emojione/emoji.json")) as f:
    emojione_json = json.load(f)
with open(os.path.join(os.path.dirname(__file__), "emoji-data/emoji.json")) as f:
    emojidata_json = json.load(f)

tone_modifiers = [
    "1f3fb",
    "1f3fc",
    "1f3fd",
    "1f3fe",
    "1f3ff"
]

emoji_dict = {
    "categories": [category.title() for category in [key for key, group in itertools.groupby([emojione["category"] for key, emojione in emojione_json.items() if emojione["category"] != "modifier"])]],
     "categoryMap": {
        category.title(): [
            {
                "name": emojione["name"].title(),
                "keywords": ",".join(emojione["keywords"]),
                "unicode": emojione["unicode"],
                "characters": "".join([chr(int(codepoint, 16)) for codepoint in emojione["unicode"].split("-")]),
                "category": emojione["category"].title(),
                "hasToneModifiers": bool(next(iter([emojidata.get("skin_variations") for emojidata in emojidata_json if emojidata["unified"].lower() == emojione["unicode"].lower()]), None)) or emojione["unicode"].split("-")[-1].lower() in tone_modifiers,
                "isToneModifier": emojione["unicode"].split("-")[-1].lower() in tone_modifiers
            } for key, emojione in emojione_json.items() if emojione["category"] == category
        ] for category in [key for key, group in itertools.groupby([emojione["category"] for key, emojione in emojione_json.items() if emojione["category"] != "modifier"])]
    },
    "emojis": [emojione["unicode"] for key, emojione in emojione_json.items() if emojione["category"] != "modifier"],
    "emojiMap": {
        emojione["unicode"]: {
            "name": emojione["name"].title(),
            "keywords": ",".join(emojione["keywords"]),
            "unicode": emojione["unicode"],
            "characters": "".join([chr(int(codepoint, 16)) for codepoint in emojione["unicode"].split("-")]),
            "category": emojione["category"].title(),
            "hasToneModifiers": bool(next(iter([emojidata.get("skin_variations") for emojidata in emojidata_json if emojidata["unified"].lower() == emojione["unicode"].lower()]), None)) or emojione["unicode"].split("-")[-1].lower() in tone_modifiers,
            "isToneModifier": emojione["unicode"].split("-")[-1].lower() in tone_modifiers
        } for key, emojione in emojione_json.items() if emojione["category"] != "modifier"
    }
}

with open(os.path.join(os.path.dirname(__file__), "emoji.json"), "w") as f:
    json.dump(emoji_dict, f, indent=4)
