import sys
import os
from androguard.core.axml import AXMLPrinter
from xml.etree.ElementTree import tostring
from xml.dom import minidom

def decompile_xml(input_file, output_dir):
    try:
        with open(input_file, 'rb') as f:
            data = f.read()
        
        axml = AXMLPrinter(data)
        xml_obj = axml.get_xml_obj()
        
        rough_string = tostring(xml_obj, 'utf-8')
        reparsed = minidom.parseString(rough_string)
        pretty_xml = reparsed.toprettyxml(indent="  ")
        
        os.makedirs(output_dir, exist_ok=True)
        
        base_name = os.path.splitext(os.path.basename(input_file))[0]
        output_file = os.path.join(output_dir, f"{base_name}_decompiled.xml")
        
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(pretty_xml)
        
        return True
        
    except Exception as e:
        print(f"失败: {e}")
        return False

def main():
    if len(sys.argv) != 3:
        sys.exit(1)
    
    input_file = sys.argv[1]
    output_dir = sys.argv[2]
    
    if not os.path.exists(input_file):
        sys.exit(1)
    
    success = decompile_xml(input_file, output_dir)
    sys.exit(0 if success else 1)

if __name__ == "__main__":
    main()