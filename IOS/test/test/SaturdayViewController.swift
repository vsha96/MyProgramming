//
//  SaturdayViewController.swift
//  test
//
//  Created by Shulyugin on 12.12.16.
//  Copyright © 2016 Shulyugin. All rights reserved.
//

import UIKit

class SaturdayViewController: UIViewController, UITableViewDelegate, UITableViewDataSource {
    var items: [String] = ["геометрия","физпрак","физпрак","алгебра","алгебра","химпрак","химпрак"]
    var time = ["9:55-10:40","10:50-11:35","11:50-12:35","12:45-13:30","13:45-14:30","14:40-15:25","15:35-16:20"]
    
    @IBOutlet weak var TableSaturday: UITableView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        TableSaturday.delegate = self
        TableSaturday.dataSource = self
        TableSaturday.tableFooterView = UIView()
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return items.count
    }
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = TableSaturday.dequeueReusableCell(withIdentifier: "CellSaturday")! as! TableViewCellMonday
        cell.LabelNameSaturday.text = items[indexPath.row]
        cell.LabelTimeSaturday.text = time[indexPath.row]
        return cell
    }
}
