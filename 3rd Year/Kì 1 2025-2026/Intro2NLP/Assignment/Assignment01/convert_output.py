import json
import openpyxl
import os

def parse_line(line):
    """
    Parses a single line from the Label.txt file.
    The line is expected to be in the format: 'image_path\tjson_string'
    """
    try:
        # Split the line at the first tab character
        image_path, json_str = line.strip().split('\t', 1)
        boxes = json.loads(json_str)
        return image_path, boxes
    except (ValueError, IndexError) as e:
        print(f"Warning: Could not parse line: {line.strip()}. Error: {e}")
        return None, None

def convert_label_to_excel(label_path="Label.txt", output_path="output.xlsx"):
    """
    Reads a Label.txt file, extracts the annotation data, and saves it
    to an Excel file with columns for ID, Image box, and Text.
    """
    # Create a new Excel workbook and select the active worksheet
    wb = openpyxl.Workbook()
    ws = wb.active
    ws.title = "OCR Output"

    ws.append(["ID", "Image box", "Text"])

    if not os.path.exists(label_path):
        print(f"Error: The file {label_path} was not found.")
        return

    with open(label_path, "r", encoding="utf-8") as f:
        lines = f.readlines()

    for idx, line in enumerate(lines, start=1):
        image_path, boxes = parse_line(line)
        
        # Skip if the line was not parsed correctly
        if boxes is None:
            continue

        # Use the page number (line number) as the ID
        page_id = idx

        # Iterate through each detected box for the current image
        for box in boxes:
            # Get the transcription and points, providing defaults if they don't exist
            text = box.get("transcription", "")
            points = box.get("points", [])
            
            ws.append([page_id, str(points), text])

    wb.save(output_path)
    print(f"Successfully converted data to {output_path}")

if __name__ == "__main__":
    convert_label_to_excel()