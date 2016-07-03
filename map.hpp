namespace cursorsio {
	class map {
		enum object_types : uint8_t {
			TEXT,
			WALL,
			EXIT,
			AREA_TRIGGER,
			BUTTON
		};
		public: 
			static std::vector<uint8_t> create_text(uint16_t x, uint16_t y, uint8_t size, bool centered, std::string string);
			static std::vector<uint8_t> create_wall(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color, uint32_t id = 0, bool isupdate = false);
			static std::vector<uint8_t> create_exit(uint16_t x, uint16_t y, uint16_t width, uint16_t height, bool isBad, uint32_t id = 0, bool isupdate = false);
			static std::vector<uint8_t> create_area(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t count, uint32_t color, uint32_t id = 0, bool isupdate = false);
			static std::vector<uint8_t> create_button(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t count, uint32_t color, uint32_t id = 0, bool isupdate = false);
			
			static void parse(cursorsio::server* s, const std::string & mapdata, std::vector<mapprop_t> & maps);
		private:
			
	};
}
