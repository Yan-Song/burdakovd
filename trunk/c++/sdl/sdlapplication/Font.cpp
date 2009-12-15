#include <map>
#include <string>
#include "Font.h"

Font::Font(const std::string& file, const int size) : font(NULL)
{
	font = TTF_OpenFont(file.c_str(), size);

	if(font == NULL)
		throw SDLException();
}

Font::~Font()
{
	if(font != NULL)
		TTF_CloseFont(font);
}

namespace
{
	class FontCache
	{
	private:
		typedef std::map<std::pair<std::string, int>, SharedFont> CacheMap;

		FontCache();

		static CacheMap cache;

	public:
		static SharedFont GetFont(const std::string& file, const int size)
		{
			std::pair<std::string, int> key(file, size);

			if(!cache.count(key))
			{
				cache[key] = SharedFont(new Font(file, size));
			}

			return cache[key];
		}

		static void Clear()
		{
			cache.clear();
		}
	};

	FontCache::CacheMap FontCache::cache;
}

SharedFont GetFont(const std::string& file, const int size)
{
	return FontCache::GetFont(file, size);
}

void ClearFontCache()
{
	FontCache::Clear();
}