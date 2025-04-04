#include "debug-memory.h"

#include <SDL3/SDL.h>

#include "../libraries/imgui/imgui.h"
#include "../common/core/clowncommon/clowncommon.h"

#if 0
void DebugMemory::DisplayInternal(const cc_u8l* const buffer, const std::size_t buffer_length)
{
#if 0
	ImGui::PushFont(window.GetMonospaceFont());

	// Fit window's width to text, and disable horizontal resizing.
	const ImGuiStyle &style = ImGui::GetStyle();
	const float width = style.ScrollbarSize + style.WindowPadding.x * 2 + ImGui::CalcTextSize("0000: 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F").x;
	ImGui::SetNextWindowSizeConstraints(ImVec2(width, 0), ImVec2(width, FLT_MAX));

	ImGui::SetNextWindowSize(ImVec2(width, width), ImGuiCond_FirstUseEver);

	ImGui::PopFont();
#endif

	ImGui::PushFont(GetMonospaceFont());

	ImGuiListClipper clipper;
	clipper.Begin(buffer_length / 0x10);
	while (clipper.Step())
	{
		for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; ++i)
		{
			const int offset = i * 0x10;
			const cc_u8l* const bytes = &buffer[offset];

			ImGui::TextFormatted("{:04X}: {:02X} {:02X} {:02X} {:02X}"
			                            " {:02X} {:02X} {:02X} {:02X}"
			                            " {:02X} {:02X} {:02X} {:02X}"
			                            " {:02X} {:02X} {:02X} {:02X}", offset,
				bytes[0x0], bytes[0x1], bytes[0x2], bytes[0x3], bytes[0x4], bytes[0x5], bytes[0x6], bytes[0x7],
				bytes[0x8], bytes[0x9], bytes[0xA], bytes[0xB], bytes[0xC], bytes[0xD], bytes[0xE], bytes[0xF]);
		}
	}

	ImGui::PopFont();
}

void DebugMemory::DisplayInternal(const cc_u16l* const buffer, const std::size_t buffer_length)
{
	// TODO: Remove or reimplement this.
#if 0
	ImGui::PushFont(window.GetMonospaceFont());

	// Fit window's width to text, and disable horizontal resizing.
	const ImGuiStyle &style = ImGui::GetStyle();
	const float width = style.ScrollbarSize + style.WindowPadding.x * 2 + ImGui::CalcTextSize("00000: 0001 0203 0405 0607 0809 0A0B 0C0D 0E0F").x;
	ImGui::SetNextWindowSizeConstraints(ImVec2(width, 0), ImVec2(width, FLT_MAX));

	ImGui::SetNextWindowSize(ImVec2(width, width), ImGuiCond_FirstUseEver);

	ImGui::PopFont();
#endif

	ImGui::PushFont(GetMonospaceFont());

	ImGuiListClipper clipper;
	clipper.Begin(buffer_length / 8);
	while (clipper.Step())
	{
		for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; ++i)
		{
			const cc_u16l* const words = &buffer[i * 8];

			ImGui::TextFormatted("{:05X}: {:04X} {:04X} {:04X} {:04X} {:04X} {:04X} {:04X} {:04X}", i * 0x10,
				words[0], words[1], words[2], words[3], words[4], words[5], words[6], words[7]);
		}
	}

	ImGui::PopFont();
}
#endif

template<>
void DebugMemory::PrintLine(const cc_u8l* const buffer, const std::size_t buffer_length_digits, const int index)
{
	const int offset = index * 0x10;
	const cc_u8l* const bytes = &buffer[offset];

	ImGui::TextFormatted("{:0{}X}: {:02X} {:02X} {:02X} {:02X}"
	                             " {:02X} {:02X} {:02X} {:02X}"
	                             " {:02X} {:02X} {:02X} {:02X}"
	                             " {:02X} {:02X} {:02X} {:02X}", offset, buffer_length_digits,
		bytes[0x0], bytes[0x1], bytes[0x2], bytes[0x3], bytes[0x4], bytes[0x5], bytes[0x6], bytes[0x7],
		bytes[0x8], bytes[0x9], bytes[0xA], bytes[0xB], bytes[0xC], bytes[0xD], bytes[0xE], bytes[0xF]);
}

template<>
void DebugMemory::PrintLine(const cc_u16l* const buffer, const std::size_t buffer_length_digits, const int index)
{
	const cc_u16l* const words = &buffer[index * 8];

	ImGui::TextFormatted("{:0{}X}: {:04X} {:04X} {:04X} {:04X} {:04X} {:04X} {:04X} {:04X}", index * 0x10, buffer_length_digits,
		words[0], words[1], words[2], words[3], words[4], words[5], words[6], words[7]);
}
